#pragma once

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <iostream>
using namespace std;

// 여기 순서 잘 맞춰야함
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <Windows.h>


// linking with WS2_32.lib (라이브러리 링킹)
#pragma comment(lib, "ws2_32.lib")