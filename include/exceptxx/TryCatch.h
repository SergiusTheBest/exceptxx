#pragma once
#include <exceptxx/ExceptionHolder.h>
#include <exceptxx/StdException.h>

#define EX_TRY(ex) exceptxx::ExceptionHolder ex; try

#define EX_CATCH(ex) \
    catch(exceptxx::BaseException& e) { ex = e.cloneMove(); } \
    catch(const std::exception& e) { ex = MAKE_STD_EXCEPTION(e); }

#define TRY_XX(ex) EX_TRY(ex)
#define CATCH_XX(ex) EX_CATCH(ex)