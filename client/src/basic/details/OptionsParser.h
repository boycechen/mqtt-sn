//
// Copyright 2016 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "option.h"

namespace mqttsn
{

namespace client
{

namespace details
{

template <typename... TOptions>
class OptionsParser;

template <>
class OptionsParser<>
{
public:
    static const bool HasClientsAllocLimit = false;
    static const bool HasTrackedGatewaysLimit = false;
    static const bool HasRegisteredTopicsLimit = false;
};

template <std::size_t TLimit, typename... TOptions>
class OptionsParser<
    mqttsn::client::option::ClientsAllocLimit<TLimit>,
    TOptions...> : public OptionsParser<TOptions...>
{
    typedef mqttsn::client::option::ClientsAllocLimit<TLimit> Option;
public:
    static const bool HasClientsAllocLimit = true;
    static const std::size_t ClientsAllocLimit = Option::Value;
};

template <std::size_t TLimit, typename... TOptions>
class OptionsParser<
    mqttsn::client::option::TrackedGatewaysLimit<TLimit>,
    TOptions...> : public OptionsParser<TOptions...>
{
    typedef mqttsn::client::option::TrackedGatewaysLimit<TLimit> Option;
public:
    static const bool HasTrackedGatewaysLimit = true;
    static const std::size_t TrackedGatewaysLimit = Option::Value;
};

template <std::size_t TLimit, typename... TOptions>
class OptionsParser<
    mqttsn::client::option::RegisteredTopicsLimit<TLimit>,
    TOptions...> : public OptionsParser<TOptions...>
{
    typedef mqttsn::client::option::RegisteredTopicsLimit<TLimit> Option;
public:
    static const bool HasRegisteredTopicsLimit = true;
    static const std::size_t RegisteredTopicsLimit = Option::Value;
};

template <typename... TTupleOptions, typename... TOptions>
class OptionsParser<
    std::tuple<TTupleOptions...>,
    TOptions...> : public OptionsParser<TTupleOptions..., TOptions...>
{
};


}  // namespace details

}  // namespace client

}  // namespace mqttsn

