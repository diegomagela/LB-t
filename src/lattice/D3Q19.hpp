#ifndef D3Q19_HPP_INCLUDED
#define D3Q19_HPP_INCLUDED

/**
 * \file     D3Q19.hpp
 * \mainpage Discretisation parameters for D3Q19-lattice
*/

#include <memory>
#include <array>

#include "../general/constexpr_func.hpp"
#include "../general/memory_alignment.hpp"

namespace lattice
{
    /**\class    D3Q19
     * \brief    Class for D3Q19 lattice
     * \warning  Static classes with more complex members such as std::vector and std::array require C++17
    */
    template <typename T = double>
    class D3Q19
    {
        public:
            /// lattice discretisation parameters
            static constexpr unsigned int    DIM =  3;
            static constexpr unsigned int SPEEDS = 19;
            static constexpr unsigned int HSPEED = (SPEEDS + 1)/2;

            /// linear memory layout padding
            static constexpr unsigned int PAD = 1;
            static constexpr unsigned int  ND = SPEEDS + PAD;
            static constexpr unsigned int OFF = ND/2;

            /// discrete velocities
            __attribute__((aligned(CACHE_LINE))) alignas(CACHE_LINE) static constexpr std::array<T, ND> DX =
            { 0,  1,  0,  0,  1,  1,  1,        //postive velocities
              1,  0,  0,
              0, -1,  0,  0, -1, -1, -1,        //negative velocities
             -1,  0,  0 };
            __attribute__((aligned(CACHE_LINE))) alignas(CACHE_LINE) static constexpr std::array<T, ND> DY =
            { 0,  0,  1,  0,  1, -1,  0,
              0,  1,  1,
              0,  0, -1,  0, -1,  1,  0,
              0, -1, -1 };
            __attribute__((aligned(CACHE_LINE))) alignas(CACHE_LINE) static constexpr std::array<T, ND> DZ =
            { 0,  0,  0,  1,  0,  0,  1,
             -1,  1, -1,
              0,  0,  0, -1,  0,  0, -1,
              1, -1,  1 };

            /// corresponding weights
            __attribute__((aligned(CACHE_LINE))) alignas(CACHE_LINE) static constexpr std::array<T, ND> W =
            { 1.0/3.0,                          //positive velocities
              1.0/8.0,  1.0/8.0,  1.0/8.0,
              1.0/36.0, 1.0/36.0, 1.0/36.0,
              1.0/36.0, 1.0/36.0, 1.0/36.0,
              1.0/3.0,                          //negative velocities
              1.0/8.0,  1.0/8.0,  1.0/8.0,
              1.0/36.0, 1.0/36.0, 1.0/36.0,
              1.0/36.0, 1.0/36.0, 1.0/36.0 };

            /// lattice speed of sound
            static constexpr T CS = 1.0/cef::sqrt(3.0);
    };
}

#endif // D3Q19_HPP_INCLUDED