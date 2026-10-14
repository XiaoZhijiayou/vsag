// Copyright 2024-present the vsag project
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy at http://www.apache.org/licenses/LICENSE-2.0
#pragma once

#include <functional>

#include "typing.h"

namespace vsag {
// Optional internal interface. Record bytes are valid only during the callback.
// Readers decode/score selected tokens without running full-document MaxSim.
class MultiVectorCodeReader {
public:
    virtual ~MultiVectorCodeReader() = default;
    virtual void
    VisitCodes(const InnerIdType* ids,
               uint64_t count,
               const std::function<void(InnerIdType, const uint8_t*)>& visitor) const = 0;
};
}  // namespace vsag
