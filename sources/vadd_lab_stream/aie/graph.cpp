// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <fstream>
#include "graph.hpp"

simpleGraph vadd_graph;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {
    vadd_graph.init();

    vadd_graph.run(1);

    vadd_graph.end();

    return 0;
}
#endif
