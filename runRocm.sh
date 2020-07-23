/home/prithayan/work/AMD/rocm/llvm/bin/clang++  -std=c++11 -isystem \
/home/prithayan/work/AMD/rocm/llvm/lib/clang/11.0.0/include/.. -isystem /opt/rocm/hsa/include -isystem \
/home/prithayan/work/AMD/rocm/hip//include -D__HIP_ARCH_GFX803__=1  --cuda-gpu-arch=gfx803 -O3 -mllvm \
-amdgpu-early-inline-all=true -mllvm -amdgpu-function-calls=false \
--hip-device-lib-path=/home/prithayan/work/AMD/rocm/lib/  -g -c -o vectoradd_hip.o -x hip vectoradd\_hip.cpp \
 -nogpulib \
		-Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/opencl.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/ocml.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/ockl.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_correctly_rounded_sqrt_off.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_daz_opt_off.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_finite_only_off.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_unsafe_math_off.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_wavefrontsize64_on.bc \
    -Xclang -mlink-bitcode-file -Xclang /home/prithayan/work/AMD/rocm/lib/amdgcn/bitcode/oclc_isa_version_900.bc 
