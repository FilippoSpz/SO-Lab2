#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_file_info(const char *path, const struct stat *file_stat) {
    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);
    const char *type;

    if (S_ISREG(file_stat->st_mode)) {
        type = "file";
    } else if (S_ISDIR(file_stat->st_mode)) {
        type = "directory";
    } else if (S_ISLNK(file_stat->st_mode)) {
        type = "symbolic link";
    } else if (S_ISFIFO(file_stat->st_mode)) {
        type = "FIFO";
    } else {
        type = "other";
    }

    printf("Node: %s\n", path);
    printf("    Inode: %lu\n", file_stat->st_ino);
    printf("    Type: %s\n", type);
    printf("    Size: %ld\n", file_stat->st_size);
    printf("    Owner: %d %s\n", file_stat->st_uid, pw->pw_name);
    printf("    Group: %d %s\n", file_stat->st_gid, gr->gr_name);
}

void list_directory(const char *dir_path, const char *root_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat file_stat;
        if (lstat(full_path, &file_stat) == -1) {
            perror("lstat");
            continue;
        }

        char relative_path[PATH_MAX];
        snprintf(relative_path, sizeof(relative_path), "%s/%s", root_path, entry->d_name);

        print_file_info(relative_path, &file_stat);

        if (S_ISDIR(file_stat.st_mode)) {
            list_directory(full_path, relative_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dir_path = argv[1];
    struct stat root_stat;
    if (lstat(dir_path, &root_stat) == -1) {
        perror("lstat");
        return EXIT_FAILURE;
    }

    print_file_info(dir_path, &root_stat);
    if (S_ISDIR(root_stat.st_mode)) {
        list_directory(dir_path, dir_path);
    }

    return EXIT_SUCCESS;
}
