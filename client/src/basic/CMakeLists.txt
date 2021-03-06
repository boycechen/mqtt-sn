macro (mqttsn_append_option list opt val)
    if (NOT "${val}" STREQUAL "")
        if (NOT "${${list}}" STREQUAL "")
            set (${list} "${${list}},")
        endif ()
        
        set (${list} "${${list}}${opt}<${val}>")
    endif () 
endmacro ()

######################################################################

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if (CC_MQTTSN_CLIENT_DEFAULT_LIB)
    gen_lib_mqttsn_client("${DEFAULT_CLIENT_NAME}" "" "" TRUE "")
endif ()    

foreach (f ${CC_MQTTSN_CUSTOM_CLIENT_CONFIG_FILES})
    if (NOT EXISTS "${f}")
        message (WARNING "File ${f} does not exist")
        continue()
    endif ()
    
    include (${f})  
    
    if ("${MQTTSN_CUSTOM_CLIENT_NAME}" STREQUAL "")
        message (WARNING "File ${f} does not specify client name!")
        continue ()
    endif ()
    
    set (mqttsn_protocol_opts)
    set (mqttsn_library_opts)
    
    mqttsn_append_option (
        mqttsn_protocol_opts 
        "mqttsn::protocol::option::ClientIdStaticStorageSize"
        "${MQTTSN_CUSTOM_CLIENT_ID_STATIC_STORAGE_SIZE}"
    )
    
    mqttsn_append_option (
        mqttsn_protocol_opts 
        "mqttsn::protocol::option::GwAddStaticStorageSize"
        "${MQTTSN_CUSTOM_CLIENT_GW_ADDR_STATIC_STORAGE_SIZE}"
    )
    
    mqttsn_append_option (
        mqttsn_protocol_opts 
        "mqttsn::protocol::option::TopicNameStaticStorageSize"
        "${MQTTSN_CUSTOM_CLIENT_TOPIC_NAME_STATIC_STORAGE_SIZE}"
    )
    
    mqttsn_append_option (
        mqttsn_protocol_opts 
        "mqttsn::protocol::option::MessageDataStaticStorageSize"
        "${MQTTSN_CUSTOM_CLIENT_MSG_DATA_STATIC_STORAGE_SIZE}"
    )
    
    mqttsn_append_option (
        mqttsn_library_opts 
        "mqttsn::client::option::ClientsAllocLimit"
        "${MQTTSN_CUSTOM_CLIENT_ALLOC_LIMIT}"
    )
    
    mqttsn_append_option (
        mqttsn_library_opts 
        "mqttsn::client::option::TrackedGatewaysLimit"
        "${MQTTSN_CUSTOM_CLIENT_TRACKED_GW_LIMIT}"
    )
    
    mqttsn_append_option (
        mqttsn_library_opts 
        "mqttsn::client::option::RegisteredTopicsLimit"
        "${MQTTSN_CUSTOM_CLIENT_REGISTERED_TOPICS_LIMIT}"
    )

    set (extra_flags)    
    if (CMAKE_COMPILER_IS_GNUCC AND MQTTSN_CUSTOM_CLIENT_NO_STDLIB)
        set (extra_flags "-nostdlib")
    endif ()
    
    
    gen_lib_mqttsn_client("${MQTTSN_CUSTOM_CLIENT_NAME}" "${mqttsn_protocol_opts}" "${mqttsn_library_opts}" TRUE "${extra_flags}")
    
    if (MQTTSN_CUSTOM_CLIENT_NO_STDLIB)
        target_compile_definitions("cc_mqttsn_${MQTTSN_CUSTOM_CLIENT_NAME}_client" PRIVATE "-DNOSTDLIB")
    endif ()
endforeach()
