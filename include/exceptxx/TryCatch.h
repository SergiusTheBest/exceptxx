#pragma once
#include <exceptxx/ExceptionHolder.h>
#include <exceptxx/StdException.h>

#define EXCEPT_XX_HOLDER(var)                           exceptxx::ExceptionHolder var
#define EXCEPT_XX_TRY_1(var)                            EXCEPT_XX_HOLDER(var); try
#define EXCEPT_XX_TRY_0()                               try

#define EXCEPT_XX_FUNC_CHOOSER(f1, f2, ...)             f2
#define EXCEPT_XX_FUNC_RECOMPOSER(argsWithParentheses)  EXCEPT_XX_FUNC_CHOOSER argsWithParentheses
#define EXCEPT_XX_CHOOSE_FROM_ARG_COUNT(...)            EXCEPT_XX_FUNC_RECOMPOSER((__VA_ARGS__, EXCEPT_XX_TRY_1,))
#define EXCEPT_XX_NO_ARG_EXPANDER()                     ,EXCEPT_XX_TRY_0
#define EXCEPT_XX_MACRO_CHOOSER(...)                    EXCEPT_XX_CHOOSE_FROM_ARG_COUNT(EXCEPT_XX_NO_ARG_EXPANDER __VA_ARGS__())
#define EXCEPT_XX_TRY(...)                              EXCEPT_XX_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define EXCEPT_XX_CATCH(var) \
    catch(exceptxx::BaseException& e) { var = e.cloneMove(); } \
    catch(const std::exception& e) { var = MAKE_STD_EXCEPTION(e); }

#define XX_TRY(...)     EXCEPT_XX_TRY(__VA_ARGS__)
#define XX_CATCH(var)   EXCEPT_XX_CATCH(var)
#define XX_HOLDER(var)  EXCEPT_XX_HOLDER(var)

#define EX_TRY(...)     EXCEPT_XX_TRY(__VA_ARGS__)
#define EX_CATCH(var)   EXCEPT_XX_CATCH(var)
#define EX_HOLDER(var)  EXCEPT_XX_HOLDER(var)
