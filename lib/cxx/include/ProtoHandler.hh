/*
 * Copyright 2009 Erik Gilling
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ProtoHandler_hh__
#define __ProtoHandler_hh__

#include <proto.h>
#include <stdint.h>

class ProtoHandler {
public:
	virtual ~ProtoHandler() {}

	virtual void relay(uint8_t idx, uint8_t state) = 0;
	virtual void light(uint8_t idx, uint8_t val) = 0;
	virtual void dpot(uint8_t idx, uint8_t val) = 0;

	virtual void resp(struct proto_packet *pkt) = 0;
};

#endif /* __ProtoHandler_hh__ */

