#ifndef ENABLE_FUNCTION_H_INCLUDED
#define ENABLE_FUNCTION_H_INCLUDED

namespace hgs{

    template<bool B, class ret_type>
    struct enable_function_if{

        template<class func, class... Args>
        static inline ret_type ejecutar(func funcion, Args... args){
            return funcion(args...);
        }

    };

    template<class ret_type>
    struct enable_function_if<false,ret_type>{

        template<class func, class... Args>
        static inline void ejecutar(func funcion, Args... args){}

    };

    template<bool B>
    struct enable_function_if<B,void>{

        template<class func, class... Args>
        static inline void ejecutar(func funcion, Args... args){
            funcion(args...);
        }

    };

    template<>
    struct enable_function_if<false,void>{

        template<class func, class... Args>
        static inline void ejecutar(func funcion, Args... args){}

    };

}


#endif // ENABLE_FUNCTION_H_INCLUDED
