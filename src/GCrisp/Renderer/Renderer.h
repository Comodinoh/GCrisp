#pragma once

#include <queue>
#include <GCrisp/Renderer/VertexArray.h>
#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Renderer/Shader.h>
#include <glm/glm.hpp>

#define MAX_RENDER_COMMANDS 1024

namespace GCrisp
{
    namespace Graphics
    {
        enum class Backend
        {
            None = 0, OpenGL = 1
        };

        struct Data
        {
            glm::mat4 ViewProjMatrix;
        };

        struct RendererProp
        {
            uint32_t MaxQuadCount = 0;
        };

        struct RenderCommand
        {
            Reference<Shader> Shader;
            Reference<VertexArray> VertexArray;
            glm::mat4 Transform;
        };

        class API
        {
        public:
            virtual ~API() = default;

            virtual void Init() = 0;

            virtual void Clear(const glm::vec4& color) const = 0;

            virtual void SetViewport(const glm::vec2& pos, const glm::vec2& size) const = 0;

            virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) const = 0;
            virtual void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t count) const = 0;

            inline static Backend GetBackend() { return s_RendererBackend; }

        protected:
            static Backend s_RendererBackend;
        };

        void Init(const RendererProp& prop);
        void Shutdown();

        void Clear(const glm::vec4& color);
        void SetViewport(const glm::vec2& pos, const glm::vec2& size);

        void DrawIndexed(const Reference<VertexArray>& vertexArray);
        void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t count);

        void BeginRender(Camera& camera);
        void EndRender();

        void Submit(const Reference<VertexArray>& vertexArray, const Reference<Shader>& shader, const glm::mat4& transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

        inline Backend GetBackend() { return API::GetBackend(); }

        static ScopedPtr<API> s_RenderAPI;
        static ScopedPtr<Data> s_Data;
        // static std::mutex s_Mutex;

        // static std::mutex& GetMutex()
        // {
        //     return s_Mutex;
        // }

        // class RenderThread
        // {
        // public:
        //     RenderThread() {};
        //     ~RenderThread();
        //
        //     void Queue(const RenderCommand& command);
        // protected:
        //     void Update();
        // private:
        //     std::vector<RenderCommand> m_Queue;
        //     std::mutex m_Mutex;
        //     std::thread m_Thread;
        // };
    }
}
