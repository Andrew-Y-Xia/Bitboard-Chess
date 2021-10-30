//
//  Search.hpp
//  SFML Chess
//
//  Created by Andrew Xia on 4/16/21.
//  Copyright © 2021 Andy. All rights reserved.
//

#ifndef Search_hpp
#define Search_hpp

#include "Board.hpp"
#include "Transposition_table.hpp"
#include "Opening_book.hpp"
#include "Time_handler.hpp"

#define MAX_DEPTH 64
#define MAXMATE 2000000
#define MINMATE 1999000
#define PRUNE_MOVE_SCORE 0

#define USE_NULL_MOVE_PRUNING 1
#define USE_ASPIRATION_WINDOWS 1
#define USE_PV_SEARCH 1
#define USE_KILLERS 1
#define USE_HIST_HEURISTIC 1
#define EXTENSION_LIMIT 5
#define USE_DELTA_PRUNING 1
#define USE_BOOK 0
#define R 2

class MovePicker {
private:
    MoveList& moves;
    bool visited[256] = {false};
    int size, visit_count;
public:
    MovePicker(MoveList& init_moves);

    bool filter_for_pruning();

    int finished();

    Move operator++();
};


struct SearchTimeout : public std::exception {
};


class Search {
private:
    Board board;
    TT& tt;
    OpeningBook& opening_book;
    TimeHandler& time_handler;

    Move killer_moves[MAX_DEPTH][2];
    unsigned int history_moves[2][64][64];

    unsigned int nodes_searched;
public:

    Search(Board b, TT& t, OpeningBook& ob, TimeHandler& th);

    template <bool use_history_heuristic = false>
    void assign_move_scores(MoveList &moves, HashMove hash_move, Move killers[2]);

    template <bool use_delta_pruning>
    void assign_move_scores_quiescent(MoveList &moves, int eval, int alpha);

    std::vector<Move> get_pv();

    void store_pos_result(HashMove best_move, unsigned int depth, unsigned int node_type, int score,
                          unsigned int ply_from_root);

    void log_search_info(int depth, int eval);

    void search_finished_message(Move best_move, int depth, int eval);

    int negamax(unsigned int depth, int alpha, int beta, unsigned int ply_from_root, unsigned int ply_extended, bool do_null_move);

    void register_killers(unsigned int ply_from_root, Move move);

    void register_history_move(unsigned int depth, Move move);

    int quiescence_search(unsigned int ply_from_horizon, int alpha, int beta, unsigned int ply_from_root);

    Move find_best_move(unsigned int max_depth);

    long perft(unsigned int depth);

    long sort_perft(unsigned int depth);

    long hash_perft(unsigned int depth);

    long hash_perft_internal(unsigned int depth);

    long capture_perft(unsigned int depth);
};

#endif /* Search_hpp */
