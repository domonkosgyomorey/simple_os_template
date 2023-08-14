SECTIONS {
    . = 0x1000;                 /* kernel potential address */

    .text : {
        *(.text)                /* the program code */
    }

    .data : {
        *(.data)                /* the initialized data */
    }

    .bss : {
        *(.bss)                 /* the uninitialized data */
    }

    /* The array address for the init functions */
    __init_funcs = .;
    /*
    The kernel stores that function which need to be executed before doing something else
    */
    .init_fun : {
        KEEP(*(.init_fun))
    }
    __init_funcs_end = .;

}