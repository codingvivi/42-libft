use std/util "repeat"

def main [] {

    let libc_fns = [
     'isalpha',
     'isdigit',
     'isalnum',
     'isascii',
     'isprint',
     'strlen',
     'memset',
     'bzero',
     'memcpy',
     'memmove',
     'strrchr',
     'strncmp',
     'strlcpy',
     'strlcat',
     'memchr',
     'memcmp',
     'toupper',
     'tolower',
     'strnstr',
     'strchr',
     'atoi',
     # 'asdf'
    ]

    let ft_names = ($libc_fns | str replace -r '^' 'ft_')
    let ft_files =  ($ft_names | str replace -r '$' '.c')

    let ref_files =  ($libc_fns | str replace -r '$' '.c')
    let ref_file_paths = (get_ref_paths $ref_files reference/musl/src)

    let fn_table = (
        $libc_fns
        | wrap 'fn'
        | merge ($ref_file_paths | wrap 'ref_path')
        | merge ($ft_names | wrap 'ft_name')
        | merge ($ft_files | wrap 'ft_file')
        | make_protos 
    )

    # print $fn_table
    create_missing_files $fn_table.ft_file
    add_libft_includes $fn_table.ft_file
    write_srcs_to_make $fn_table.ft_file
    write_protos_to_files $fn_table


}


def get_ref_paths [fn_names: list, ref_dir: path] {

    # print_cli_header 'Get reference paths'
    
    let all_ref_files = (ls -a reference/musl/**/* | get name)

    $fn_names
    | each {|fn_to_find|
        try {
            $all_ref_files
            | where ($it | path basename  ) =~ $fn_to_find
            | first 
        } catch {
            ''
        }
    }

}

def make_protos [] {
    each {|row|
        $row
        | insert ref_protos (
            if ($row.ref_path | is-empty) {
                null
            } else {
                try {
                    open $row.ref_path
                    | lines 
                    | where $it =~ $row.fn
                    | where $it =~ '\('
                    | where not ($it | str starts-with '#')  
                    | where not ($it | str starts-with '//') 
                    | where not ($it | str contains '/*')    
                    | first
                    | str replace -r '^' 'ft_'
                } catch {
                    null
                }
            }
        )
    }
}


def create_missing_files [file_list: list] {

    print_cli_header 'Create_missing files'
    
    print $'($file_list | length) files in total'

    let files_to_create = ($file_list | where not ($it | path exists))

    print $'($files_to_create| length) files missing'
    print ''

    let num_files_created = (
        $files_to_create
        | each {|curr_path|
            touch $curr_path
            print $'created ($curr_path)'
            $curr_path
        }
        | length
    )

    print $"File creation done! Created ($num_files_created) files in total."
    if ($num_files_created > 0) {
        print 'How touching 🥹'
    } else {
        print 'Not very touching 🥀'
    }    
    print_padding 
}


def add_libft_includes [files: list] {

    print_cli_header 'Add library include line'

    let include_str =  '#include "libft.h"'
    print $'string to add: ($include_str)'

    #get total files
    let files_missing_lib = rg --files-without-match $include_str ...$files | lines

    if ($files_missing_lib | is-empty) {
        print "no files missing string"
    } else {
        
        let empty_ln_rx = '^$' 

        let files_wo_empty_ln = (
            $files_missing_lib
            | rg --files-without-match $empty_ln_rx ...$in 
            | lines 
            | wrap "name"
            | insert line_number { 0 }
        )

        let files_w_empty_ln = (
            $files_missing_lib
            | rg -m 1 -n $empty_ln_rx ...$in
            | lines
            | split column ":" name line_number 
        )

        let files_table = ($files_w_empty_ln | append $files_wo_empty_ln)

        print $'adding to ($files_table | length) files'

        $files_table
        | each {|row|
            let file_name = $row.name
            let ln_insert = (
                $row.line_number
                | into int
                | if $in > 0 {
                    $in - 1
                } else {
                    0
                }
            )
    
            let new_content = (
                open $file_name
                | lines
                | insert $ln_insert $include_str
                | insert ($ln_insert + 1) '' 
                | str join (char newline)
            )
    
            $new_content | save -f $file_name
    
            print $"Added include to file '($file_name)' at line ($ln_insert)"
        }
    }
    print_padding 
}

def write_srcs_to_make [files: list] {
    
    print_cli_header 'write SRCes to Makefile'

    let src_string = (
        $files
        | str replace -r '^' (char tab)
        | str join " \\ \n" 
    )
    let src_declare =  'SRCS = '

    let makefile_contents = open 'Makefile'
    if ($makefile_contents | str contains $src_declare) {
        print 'File already has sources. skipping...'
    } else {
        (
            $makefile_contents
            | lines
            | insert 1 $src_declare
            | insert 2 $src_string
            | str join (char newline)
            | printf $in
        )
        | save -f Makefile
        print 'Added SRCS variable with value!'
    }
    print_padding 
}


def print_cli_header [title:string] {
    print $title
    let str_len =  ($title |str length )
    print ('~' | repeat $str_len |str join)
}

def print_padding [] {
    print 'EOF'
    print ('-' | repeat 8 | str join)
    print ''
}

# def print_header [string: string] {
    
# }    

def write_protos_to_files [fn_table: table] {

    print_cli_header 'Add missing prototypes'

    let candidates_list = ($fn_table | where {|row| $row.ref_protos | is-not-empty})

    print $"($candidates_list | length) prototypes in total"

    $candidates_list
    | each {|row|
        let file = $row.ft_file
        let file_contents = (open $file)

        $file_contents
            | lines
            | if ($in
                | any {|line|
                    $line
                    | strip_whitespace
                    | str contains ($row.ref_protos | strip_whitespace)
                }
            ) {
                print $'($file) alreay contains prototype'
            } else {
                print "bag"
            }
        
            # | any {|line|
                # ($line | str replace -ar '\s+' ' ' | str trim)
             # }
         }
    #             | like ($row.protos | str replace -ar '\s+' ' ' | str trim)
    #         }
    #     )

    #     if not $file_contains_proto {
    #         let str = $'($row.ref_protos)\n{\n}'
    #         print $'appending ($str) to file:($row.ft_file)'
    #         # $row.ft_files | save --append $row.ft_files

    #     }
    # }
    # | length | print $'Added to ($in) new files'

    # print_padding 
}

def strip_whitespace []  {
     str replace -r -a ' |\t' '' 
}

def get_first_empty_line [] {
    rg -m 1 -n '^$' 
    | if ($in | is-not-empty) {
        $in | into int
    } else {
        0
    }
}
