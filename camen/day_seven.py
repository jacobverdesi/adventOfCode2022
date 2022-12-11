#! /usr/bin/env python3


SIZE_KEY = "____SIZE"


def record_cd(current_directory, to_directory_name, current_path, filesystem):
    if to_directory_name == "..":
        current_path.pop()
        current_directory = filesystem[current_path[0]]
        for directory_name in current_path[1:]:
            current_directory = current_directory[directory_name]

    else:
        current_directory[to_directory_name] = current_directory.get(
            to_directory_name, {}
        )
        current_directory = current_directory[to_directory_name]
        current_path.append(to_directory_name)

    return current_directory, current_path


def record_ls(current_directory, output, current_path, filesystem):
    current_directory_size = 0

    for item in output:
        location_type, location_name = item.split(" ")

        if location_type == "dir":
            current_directory[location_name] = current_directory.get(location_name, {})
        else:
            location_size = location_type
            current_directory[location_name] = int(location_size)
            current_directory_size += int(location_size)

    update_filesystem_size(current_directory_size, current_path, filesystem)
    return current_directory


def update_filesystem_size(size, path, filesystem):
    filesystem[SIZE_KEY] = filesystem.get(SIZE_KEY, 0) + size

    current_directory = filesystem
    for next_directory in path:
        current_directory = current_directory[next_directory]
        current_directory[SIZE_KEY] = current_directory.get(SIZE_KEY, 0) + size


def parse_filesystem(terminal):
    terminal_lines = terminal.strip().split("$ ")

    filesystem = {}
    current_directory = None
    current_path = []
    for terminal_line in terminal_lines[1:]:
        command, *output = terminal_line.strip().split("\n")

        if command.startswith("cd"):
            _, directory_name = command.split(" ")
            current_directory, current_path = record_cd(
                current_directory=current_directory
                if current_directory is not None
                else filesystem,
                to_directory_name=directory_name,
                current_path=current_path,
                filesystem=filesystem,
            )
        elif command.startswith("ls"):
            current_directory = record_ls(
                current_directory=current_directory,
                output=output,
                current_path=current_path,
                filesystem=filesystem,
            )
    return filesystem


def get_directory_sizes(directory, name):
    sizes = []
    for key, value in directory.items():
        if isinstance(value, dict):
            subsystem = value
            sizes += get_directory_sizes(directory=subsystem, name=key)
        elif key == SIZE_KEY:
            sizes.append((name, value))
    return sizes


def score_1(filesystem):
    return sum(
        x[1] for x in get_directory_sizes(filesystem, name="root") if x[1] <= 100_000
    )


def score_2(filesystem, space_needed=30_000_000, total_size=70_000_000):
    filesystem_size = filesystem[SIZE_KEY]
    to_free_up = space_needed - (total_size - filesystem_size)

    if to_free_up <= 0:
        return None

    best_directory = "/"
    best_directory_size = filesystem_size
    for directory, size in get_directory_sizes(filesystem, name="root"):
        extra_space = size - to_free_up
        if 0 <= extra_space < best_directory_size - to_free_up:
            best_directory = directory
            best_directory_size = size

    return best_directory_size


def main():
    with open("resources/day_seven_input.txt") as buffer:
        terminal = buffer.read()

    filesystem = parse_filesystem(terminal)
    answer_one = score_1(filesystem)
    answer_two = score_2(filesystem)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
