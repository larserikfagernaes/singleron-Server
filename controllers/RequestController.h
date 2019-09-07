#pragma once
#undef WARN
#undef ERROR
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class RequestController:public drogon::HttpSimpleController<RequestController>
{
public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/processData",Post);
    //PATH_ADD("/path","filter1","filter2",HttpMethod1,HttpMethod2...);
    PATH_LIST_END
};
