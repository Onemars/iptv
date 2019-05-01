/*  Copyright (C) 2014-2019 FastoGT. All right reserved.
    This file is part of iptv_cloud.
    iptv_cloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    iptv_cloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with iptv_cloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <common/libev/io_child.h>

#include "protocol/protocol.h"

#include "base/types.h"

namespace iptv_cloud {
struct StreamStruct;
namespace server {

class ChildStream : public common::libev::IoChild {
 public:
  typedef common::libev::IoChild base_class;
  typedef protocol::protocol_client_t client_t;
  ChildStream(common::libev::IoLoop* server, StreamStruct* mem);

  common::ErrnoError SendStop(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError SendRestart(protocol::sequance_id_t id) WARN_UNUSED_RESULT;

  stream_id_t GetStreamID() const;

  bool Equals(const ChildStream& stream) const;

  StreamStruct* GetMem() const;

  client_t* GetClient() const;
  void SetClient(client_t* pipe);

 private:
  StreamStruct* const mem_;
  client_t* client_;

  DISALLOW_COPY_AND_ASSIGN(ChildStream);
};

inline bool operator==(const ChildStream& left, const ChildStream& right) {
  return left.Equals(right);
}

inline bool operator!=(const ChildStream& left, const ChildStream& right) {
  return !operator==(left, right);
}

}  // namespace server
}  // namespace iptv_cloud
