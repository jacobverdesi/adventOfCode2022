#! /usr/bin/env python3


def transform_coordinates(row_, column_, view_angle, dimension_size):
    # coordinates = (row, column)
    # left = as is
    # top = row=column_, column=row_
    # right = row=row_, column=len(row_)-column_
    # bottom = row=len(row)-column_, column=row
    if view_angle == "left":
        return (row_, column_)
    if view_angle == "right":
        return (row_, dimension_size - 1 - column_)
    if view_angle == "top":
        return (column_, row_)
    if view_angle == "bottom":
        return (dimension_size - 1 - column_, row_)
    raise AssertionError(
        f"view_angle must be one of left,right,top,bottom! Got {view_angle}"
    )


def get_viewable_trees(tree_heights, view_angle):
    viewable_trees = set()
    dimension_size = len(tree_heights)

    for row_idx, tree_set in enumerate(tree_heights):

        max_in_row = None
        for col_idx, tree_height in enumerate(tree_set):

            if (max_in_row is None) or (tree_height > max_in_row):
                viewable_trees.add(
                    transform_coordinates(
                        row_idx,
                        col_idx,
                        view_angle=view_angle,
                        dimension_size=dimension_size,
                    )
                )

                max_in_row = tree_height

    return viewable_trees


def score_1(tree_heights):
    left = tree_heights
    top = list(zip(*left))
    right = list(map(lambda x: tuple(reversed(x)), left))
    bottom = list(map(lambda x: tuple(reversed(x)), top))

    viewable_trees = set()
    for view_angle_name, tree_heights_ in zip(
        ["left", "top", "right", "bottom"], [left, top, right, bottom]
    ):
        viewable_trees.update(
            get_viewable_trees(
                tree_heights=tree_heights_,
                view_angle=view_angle_name,
            )
        )

    return len(viewable_trees)


def count_trees_seen_left(tree_idx, trees):
    row_idx = tree_idx[0]
    max_height = trees[tree_idx[0]][tree_idx[1]]

    trees_seen = 0
    for col_idx in range(tree_idx[1] - 1, -1, -1):
        tree = trees[row_idx][col_idx]

        if tree >= max_height:
            trees_seen += 1
            break

        trees_seen += 1

    return trees_seen


def count_trees_seen_up(tree_idx, trees):
    col_idx = tree_idx[1]
    max_height = trees[tree_idx[0]][tree_idx[1]]

    trees_seen = 0
    for row_idx in range(tree_idx[0] - 1, -1, -1):
        tree = trees[row_idx][col_idx]

        if tree >= max_height:
            trees_seen += 1
            break

        trees_seen += 1

    return trees_seen


def count_trees_seen_right(tree_idx, trees):
    row_idx = tree_idx[0]
    max_height = trees[tree_idx[0]][tree_idx[1]]

    trees_seen = 0
    for col_idx in range(tree_idx[1] + 1, len(trees[0])):
        tree = trees[row_idx][col_idx]

        if tree >= max_height:
            trees_seen += 1
            break

        trees_seen += 1

    return trees_seen


def count_trees_seen_down(tree_idx, trees):
    col_idx = tree_idx[1]
    max_height = trees[tree_idx[0]][tree_idx[1]]

    trees_seen = 0
    for row_idx in range(tree_idx[0] + 1, len(trees)):
        tree = trees[row_idx][col_idx]

        if tree >= max_height:
            trees_seen += 1
            break

        trees_seen += 1

    return trees_seen


def score_2(tree_heights):
    scores = []
    for row_idx in range(len(tree_heights)):
        for col_idx in range(len(tree_heights[0])):
            left = count_trees_seen_left((row_idx, col_idx), tree_heights)
            right = count_trees_seen_right((row_idx, col_idx), tree_heights)
            up = count_trees_seen_up((row_idx, col_idx), tree_heights)
            down = count_trees_seen_down((row_idx, col_idx), tree_heights)
            scores.append(left * right * up * down)

    return max(scores)


def main():
    with open("resources/day_eight_input.txt") as buffer:
        tree_heights = buffer.readlines()

    tree_heights = [tuple(map(int, tree_row.strip())) for tree_row in tree_heights]
    answer_one = score_1(tree_heights)
    answer_two = score_2(tree_heights)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
