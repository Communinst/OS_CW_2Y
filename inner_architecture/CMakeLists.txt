
cmake_minimum_required (VERSION 3.21)
project (os_cw_nnr_rchtctr)

add_library(
    os_cw_nnr_rchtctr
    src/inner_architecture.cpp)

target_include_directories (
    os_cw_nnr_rchtctr
    PUBLIC
    ./include)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_rlvnt_tp)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_assctv_cntnr_srch_tr_indxng_tr_b_tr)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_assctv_cntnr_srch_tr)


target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_dc_utlts)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_ipc)


target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC 
    os_cw_allctr_allctr)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_allctr_allctr_glbl_hp)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_allctr_allctr_bndr_tgs)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_allctr_allctr)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_lggr_lggr)

target_link_libraries (
    os_cw_nnr_rchtctr
    PUBLIC
    os_cw_cor_pttrn)


#set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")

set_target_properties (
    os_cw_nnr_rchtctr PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION 1.0
    DESCRIPTION "inner architecture library")