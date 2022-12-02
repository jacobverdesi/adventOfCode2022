#! /usr/bin/env python3
MOVE_SCORES = {
    "rock": 1,
    "paper": 2,
    "scissors": 3,
}

RESULT_SCORES = {
    "win": 6,
    "tie": 3,
    "lose": 0,
}

OPPONENTS_MOVES = {
    "A": "rock",
    "B": "paper",
    "C": "scissors",
}

OUTCOMES = {  # (opponent's move, your move)
    ("rock", "rock"): "tie",
    ("paper", "rock"): "lose",
    ("scissors", "rock"): "win",
    ("rock", "paper"): "win",
    ("paper", "paper"): "tie",
    ("scissors", "paper"): "lose",
    ("rock", "scissors"): "lose",
    ("paper", "scissors"): "win",
    ("scissors", "scissors"): "tie",
}


def score_1(game):
    your_moves = {
        "X": "rock",
        "Y": "paper",
        "Z": "scissors",
    }
    opponents_move, your_move = game

    opponents_move = OPPONENTS_MOVES[opponents_move]
    your_move = your_moves[your_move]

    your_move_score = MOVE_SCORES[your_move]
    outcome = OUTCOMES[(opponents_move, your_move)]
    result_score = RESULT_SCORES[outcome]
    return result_score + your_move_score


def score_2(game):
    outcomes = {
        "X": "lose",
        "Y": "tie",
        "Z": "win",
    }
    your_moves = {
        (opponents_move, outcome): your_move
        for (opponents_move, your_move), outcome in OUTCOMES.items()
    }

    opponents_move, outcome = game
    opponents_move = OPPONENTS_MOVES[opponents_move]
    outcome = outcomes[outcome]
    your_move = your_moves[(opponents_move, outcome)]

    your_move_score = MOVE_SCORES[your_move]
    result_score = RESULT_SCORES[outcome]
    return result_score + your_move_score


def main():
    with open("resources/day_two_input.txt") as buffer:
        games = buffer.readlines()

    your_scores_1 = map(lambda game: score_1(game.strip().split(" ")), games)
    your_scores_2 = map(lambda game: score_2(game.strip().split(" ")), games)

    answer_one = sum(your_scores_1)
    answer_two = sum(your_scores_2)
    print(f"Answer one: {answer_one}")
    print(f"Answer two: {answer_two}")


if __name__ == "__main__":
    main()
