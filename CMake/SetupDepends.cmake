include(LogFeature)
include(PkgUtils)
prepare_dep_search(NODEJS_NGE2)

################################################################################
# nge2
set(NODEJS_NGE2_DEP_LIBS)
# Find zlib
find_package(NGE2)
log_feature(NGE2_FOUND "libnge2" "library to wrap" "http://github.com/ifreedom/libnge2" REQUIRED)
add_package(NGE2 NODEJS_NGE2_DEP_LIBS)

################################################################################
# Tools
find_package(Doxygen)
log_feature(DOXYGEN_FOUND "Doxygen" "Tool for building API documentation" "http://doxygen.org")

# Display results, terminate if anything required is missing
set(MISS_FEATURE_CUSTOM_MSG "-- If you are in Windows, try passing -DNODEJS_NGE2_DEPENDENCIES_DIR=<path to dependencies>")
display_feature_log()
