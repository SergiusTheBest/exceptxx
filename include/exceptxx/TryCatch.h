#pragma once
#include <exceptxx/ExceptionHolder.h>
#include <exceptxx/StdException.h>

#define EXCEPTXX_HOLDER(var)                            exceptxx::ExceptionHolder var
#define EXCEPTXX_TRY_1(var)                             EXCEPTXX_HOLDER(var); try
#define EXCEPTXX_TRY_0()                                try

#define EXCEPTXX_FUNC_CHOOSER(f1, f2, ...)              f2
#define EXCEPTXX_FUNC_RECOMPOSER(argsWithParentheses)   EXCEPTXX_FUNC_CHOOSER argsWithParentheses
#define EXCEPTXX_CHOOSE_FROM_ARG_COUNT(...)             EXCEPTXX_FUNC_RECOMPOSER((__VA_ARGS__, EXCEPTXX_TRY_1,))
#define EXCEPTXX_NO_ARG_EXPANDER()                      ,EXCEPTXX_TRY_0
#define EXCEPTXX_MACRO_CHOOSER(...)                     EXCEPTXX_CHOOSE_FROM_ARG_COUNT(EXCEPTXX_NO_ARG_EXPANDER __VA_ARGS__())
#define EXCEPTXX_TRY(...)                               EXCEPTXX_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define EXCEPTXX_CATCH(var) \
    catch(exceptxx::BaseException& e) { var = e.cloneMove(); } \
    catch(const std::exception& e) { var = EXCEPTXX_MAKE_STD_EXCEPTION(e); }

#define XX_TRY(...)     EXCEPTXX_TRY(__VA_ARGS__)
#define XX_CATCH(var)   EXCEPTXX_CATCH(var)
#define XX_HOLDER(var)  EXCEPTXX_HOLDER(var)

#define EX_TRY(...)     EXCEPTXX_TRY(__VA_ARGS__)
#define EX_CATCH(var)   EXCEPTXX_CATCH(var)
#define EX_HOLDER(var)  EXCEPTXX_HOLDER(var)
