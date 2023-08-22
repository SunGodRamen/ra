#include "raw_hid_command.h"

static void get_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle GET logic here ...
}
raw_hid_command get_command = {
    .execute = get_execute
};

static void post_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle POST logic here ...
}
raw_hid_command post_command = {
    .execute = post_execute
};

static void put_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle PUT logic here ...
}
raw_hid_command put_command = {
    .execute = put_execute
};

static void patch_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle PATCH logic here ...
}
raw_hid_command patch_command = {
    .execute = patch_execute
};

static void delete_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle DELETE logic here ...
}
raw_hid_command delete_command = {
    .execute = delete_execute
};

static void connect_execute(raw_hid_request *request, raw_hid_response *response) {
    // ... handle CONNECT logic here ...
}
raw_hid_command connect_command = {
    .execute = connect_execute
};

void raw_hid_manager_init() {
    command_registry[_GET] = &get_command;
    command_registry[_POST] = &post_command;
    command_registry[_PUT] = &put_command;
    command_registry[_PATCH] = &patch_command;
    command_registry[_DELETE] = &delete_command;
    command_registry[_CONNECT] = &connect_command;
}
