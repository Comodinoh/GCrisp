#pragma once

namespace GCrisp
{
    namespace Graphics
    {
        class Context
        {
        public:
            virtual void Init() const = 0;

            virtual void SwapBuffers() const = 0;
        };
    }
}
