# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seantywork/main/multi-terminal-games/cmake/mtgms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seantywork/main/multi-terminal-games/cmake/mtgms/build

# Include any dependencies generated for this target.
include CMakeFiles/mtgms_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mtgms_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mtgms_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mtgms_client.dir/flags.make

CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o: CMakeFiles/mtgms_client.dir/flags.make
CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o: /home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc
CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o: CMakeFiles/mtgms_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seantywork/main/multi-terminal-games/cmake/mtgms/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o -MF CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o.d -o CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o -c /home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc

CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc > CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.i

CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc -o CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.s

# Object files for target mtgms_client
mtgms_client_OBJECTS = \
"CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o"

# External object files for target mtgms_client
mtgms_client_EXTERNAL_OBJECTS =

mtgms_client: CMakeFiles/mtgms_client.dir/home/seantywork/main/multi-terminal-games/terminal/mtgms/mtgms_client.cc.o
mtgms_client: CMakeFiles/mtgms_client.dir/build.make
mtgms_client: libmtgms_grpc_proto.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_parse.a
mtgms_client: /home/seantywork/.grpc/lib/libgrpc++_reflection.a
mtgms_client: /home/seantywork/.grpc/lib/libgrpc++.a
mtgms_client: /home/seantywork/.grpc/lib/libprotobuf.a
mtgms_client: /home/seantywork/.grpc/lib/libgrpc.a
mtgms_client: /home/seantywork/.grpc/lib/libupb_collections_lib.a
mtgms_client: /home/seantywork/.grpc/lib/libupb_json_lib.a
mtgms_client: /home/seantywork/.grpc/lib/libupb_textformat_lib.a
mtgms_client: /home/seantywork/.grpc/lib/libutf8_range_lib.a
mtgms_client: /home/seantywork/.grpc/lib/libupb.a
mtgms_client: /home/seantywork/.grpc/lib/libre2.a
mtgms_client: /home/seantywork/.grpc/lib/libz.a
mtgms_client: /home/seantywork/.grpc/lib/libcares.a
mtgms_client: /home/seantywork/.grpc/lib/libgpr.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_distributions.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_seed_sequences.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_pool_urbg.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_randen.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_randen_hwaes.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_randen_hwaes_impl.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_randen_slow.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_platform.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_internal_seed_material.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_random_seed_gen_exception.a
mtgms_client: /home/seantywork/.grpc/lib/libssl.a
mtgms_client: /home/seantywork/.grpc/lib/libcrypto.a
mtgms_client: /home/seantywork/.grpc/lib/libaddress_sorting.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_check_op.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_leak_check.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_die_if_null.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_conditions.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_message.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_nullguard.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_examine_stack.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_format.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_proto.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_log_sink_set.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_sink.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_entry.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_initialize.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_globals.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_internal_globals.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_statusor.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_status.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_strerror.a
mtgms_client: /home/seantywork/.grpc/lib/libutf8_validity.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_usage.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_usage_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_marshalling.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_reflection.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_config.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_private_handle_accessor.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_commandlineflag.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_commandlineflag_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_flags_program_name.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_cord.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_cordz_info.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_cord_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_cordz_functions.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_cordz_handle.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_crc_cord_state.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_crc32c.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_str_format_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_crc_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_crc_cpu_detect.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_raw_hash_set.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_hash.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_bad_variant_access.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_city.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_low_level_hash.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_bad_optional_access.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_hashtablez_sampler.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_exponential_biased.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_synchronization.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_graphcycles_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_kernel_timeout_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_time.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_civil_time.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_time_zone.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_stacktrace.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_symbolize.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_strings.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_string_view.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_strings_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_int128.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_throw_delegate.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_malloc_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_debugging_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_demangle_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_base.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_raw_logging_internal.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_log_severity.a
mtgms_client: /home/seantywork/.grpc/lib/libabsl_spinlock_wait.a
mtgms_client: CMakeFiles/mtgms_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seantywork/main/multi-terminal-games/cmake/mtgms/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mtgms_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mtgms_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mtgms_client.dir/build: mtgms_client
.PHONY : CMakeFiles/mtgms_client.dir/build

CMakeFiles/mtgms_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mtgms_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mtgms_client.dir/clean

CMakeFiles/mtgms_client.dir/depend:
	cd /home/seantywork/main/multi-terminal-games/cmake/mtgms/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seantywork/main/multi-terminal-games/cmake/mtgms /home/seantywork/main/multi-terminal-games/cmake/mtgms /home/seantywork/main/multi-terminal-games/cmake/mtgms/build /home/seantywork/main/multi-terminal-games/cmake/mtgms/build /home/seantywork/main/multi-terminal-games/cmake/mtgms/build/CMakeFiles/mtgms_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mtgms_client.dir/depend
