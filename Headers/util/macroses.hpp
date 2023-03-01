#pragma once

#define SPRSIM_S1(x) #x
#define SPRSIM_S2(x) SPRSIM_S1(x)
#define LOCATION "  Location: " __FILE__ " : " SPRSIM_S2(__LINE__) " line"
