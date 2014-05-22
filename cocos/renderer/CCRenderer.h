/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "base/CCPlatformMacros.h"
#include "CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

NS_CC_BEGIN

class EventListenerCustom;
class QuadCommand;

/**  一个知道如何对RenderCommand对象排序的类。
   因为具有 "z == 0"的命令会被加入到正确的顺序里，唯一需要被排序的RenderCommand对象是那些 'z < 0 '和'z > 0 '的对象。
*/
class RenderQueue {

public:
    void push_back(RenderCommand* command);
    ssize_t size() const;
    void sort();
    RenderCommand* operator[](ssize_t index) const;
    void clear();

protected:
    std::vector<RenderCommand*> _queueNegZ;
    std::vector<RenderCommand*> _queue0;
    std::vector<RenderCommand*> _queuePosZ;
};

struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class GroupCommandManager;

/* 负责渲染(render)的类
    任何时候尽可能地使用QuadCommand对象,因为渲染器会自动批量对它们进行处理。
 */
class Renderer
{
public:
    static const int VBO_SIZE = 65536 / 6;
    static const int BATCH_QUADCOMMAND_RESEVER_SIZE = 64;

    Renderer();
    ~Renderer();

    //TODO 在Render里独立管理GLView.
    void initGLView();

    /** 增加一个RenderCommand对象到渲染器中 */
    void addCommand(RenderCommand* command);

    /** 通过指定一个特殊的渲染队列(render queue)ID来增加一个RenderCommand 对象到渲染器中。 */
    void addCommand(RenderCommand* command, int renderQueue);

    /** 把一个组(group)放进渲染队列（render queue)的队尾 */
    void pushGroup(int renderQueueID);

    /** 把一个组(group)从渲染队列(render queue)的队首拿出 */
    void popGroup();

    /** 创建一个渲染队列(render queue) 并返回它的ID */
    int createRenderQueue();

    /** 在GLView上渲染所有被放进队列的RenderCommand对象 */
    void render();

    /** 清除队列里所有RenderCommand对象 */
    void clean();

    /* 返回在上一帧(frame)画了的batch的数目 */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* RenderCommand对象(除了QuadCommand对象)应该更新这个值 */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* 返回在上一帧(frame)画了的三角形(triangles)的数目 */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* RenderCommand对象(除了QuadCommand对象)应该更新这个值 */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };

    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

    /** 返回一个矩形是否可见 */
    bool checkVisibility(const Mat4& transform, const Size& size);

protected:

    void setupIndices();
    //基于OpenGL的扩展设置VBO或VAO
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();

    void drawBatchedQuads();

    //去除（flush）之前的环境上下文(context),画预览被放进队列中得quads
    void flush();
    
    void visitRenderQueue(const RenderQueue& queue);

    void convertToWorldCoordinates(V3F_C4B_T2F_Quad* quads, ssize_t quantity, const Mat4& modelView);

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    std::vector<QuadCommand*> _batchedQuadCommands;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: 顶点  1: 索引

    int _numQuads;
    
    bool _glViewAssigned;

    // stats
    ssize_t _drawnBatches;
    ssize_t _drawnVertices;
    //检查渲染器是否正在渲染的标记
    bool _isRendering;
    
    GroupCommandManager* _groupCommandManager;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

#endif //__CC_RENDERER_H_
