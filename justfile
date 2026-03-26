build *args:
    make {{args}}
    rsync -av --include-from='.turnin-include' --exclude='*' . turnin/

turnin-sync:
    rsync -av --include-from='.turnin-include' --exclude='*' . turnin/
