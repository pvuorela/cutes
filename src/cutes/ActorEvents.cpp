#include "ActorEvents.hpp"
#include "ActorEvents.moc"
#include "Env.hpp"
#include "QmlAdapter.hpp"

//#include <cutes/util.hpp>
#include "qt_quick_types.hpp"
#include <QDebug>
#include <QCoreApplication>

namespace cutes {

Endpoint::Endpoint(QJSValue const& on_reply
                   , QJSValue const& on_error
                   , QJSValue const& on_progress
                   , std::unique_ptr<ActorHolder> h)
    : on_reply_(on_reply)
    , on_error_(on_error)
    , on_progress_(on_progress)
    , actor_holder_(std::move(h))
{
}

Endpoint::~Endpoint()
{
}

Load::Load(QString const &src, QString const& top_script
           , std::unique_ptr<ActorHolder> holder)
    : Event(Event::LoadScript)
    ,  src_(src)
    , top_script_(top_script)
    , actor_holder_(std::move(holder))
{}

Load::Load(Load &&src)
    : Event(Event::LoadScript)
    ,  src_(src.src_)
    , top_script_(src.top_script_)
    , actor_holder_(std::move(src.actor_holder_))
{}

Load::~Load() {}

LoadError::LoadError(QVariant const &info, std::unique_ptr<ActorHolder> holder)
    : Event(Event::LoadException)
    , info_(info)
    , actor_holder_(std::move(holder))
{}

LoadError::~LoadError() {}

Message::Message(QVariant const& data, endpoint_handle ep
                 , Event::Type type)
    : Event(type), data_(data), endpoint_(ep)
{}

Message::~Message() {}

Request::Request(QString const &method_name, QVariant const& data
                 , endpoint_handle ep, Event::Type type)
    : Message(data, ep, type)
    , method_name_(method_name)
{}

Request::~Request() {}

EndpointRemove::EndpointRemove(Endpoint *p)
    : Event(Event::EndpointRemove)
    , endpoint_(p)
{}

EndpointRemove::~EndpointRemove() {}

}
