#ifndef ISR80H_H
#define ISR80H_H

enum SystemCommands {
    SYSTEM_COMMAND0_SUM,
    SYSTEM_COMMAND1_PRINT,
    SYSTEM_COMMAND2_GET_KEY,
    SYSTEM_COMMAND3_PUT_CHAR,
    SYSTEM_COMMAND4_MALLOC,
};

void isr80h_register_commands();

#endif