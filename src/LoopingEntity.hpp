#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include <string>
#include <exception>

namespace kpg
{
    class EntityLoopException : public std::exception
    {
    public:
        EntityLoopException(std::string exception)
        {
            err = exception;
        }
        
    private:
        std::string err;
        const char * what () const throw ()
        {
            return err.c_str();
        }
        
    };

    class LoopingEntity
    {
    protected:
        bool end = false;
        uint32_t Period; // In milliseconds
    private:
        uint64_t ID;
        virtual bool OnCreate() = 0;
        virtual bool OnUpdate() = 0;
        virtual bool OnDestroy() = 0;
        void CalcThread();
    public:
        bool Spawn();
    };

}

#endif /* LoopingEntity_hpp */
