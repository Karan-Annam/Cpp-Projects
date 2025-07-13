#include <iostream>
#include <vector>
#include <string>

void initializeBoard(std::vector<std::vector<bool>>& board);
void updateBoard(std::vector<std::vector<bool>>& board);
bool checkCell(std::vector<std::vector<bool>>& board, int row, int col);

constexpr int start_size = 10;

int main(void){
    std::vector<std::vector<bool>> board(start_size, std::vector<bool>(start_size, 0));
    
    initializeBoard(board);
    std::cout << "Initial Board State:" << std::endl; 
    for (auto& i : board){
        for (int b : i){
            std::cout << b;
        }
        std::cout << std::endl;
    }

    //sketch way to clear buffer before reading again
    std::string line;
    std::getline(std::cin, line);

    while(true){
        std::getline(std::cin, line);
        if(line.empty()){
            updateBoard(board);
        } else{
            break;
        }
    }
}

void updateBoard(std::vector<std::vector<bool>>& board){
    std::vector<std::vector<bool>> tempboard = board;
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++){
            tempboard[i][j] = checkCell(board, i, j);
        }
    }

    board = tempboard;

    for (auto& i : board){
        for (int b : i){
            std::cout << b;
        }
        std::cout << std::endl;
    }
}

/*Birth: A dead cell with exactly three live neighbors becomes a live cell. 
Survival: A live cell with two or three live neighbors lives on to the next generation. 
Death: A live cell with fewer than two live neighbors dies (underpopulation), and a live cell with more than three live neighbors dies (overpopulation). */
bool checkCell(std::vector<std::vector<bool>>& board, int row, int col){
    std::vector<std::pair<int, int>> neighbors = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    int alive = 0;
    for (auto& p : neighbors){
        int rowtemp = row + p.first;
        int coltemp = col + p.second;
        if(rowtemp < 0 || rowtemp >= start_size || coltemp < 0 || coltemp >= start_size){
            continue;
        }

        if(board[rowtemp][coltemp] == true){ alive++; }
    }
    
    if(board[row][col] == false){
        if(alive == 3){return true;}
        else return false;
    }
    else{
        if(alive == 2 || alive == 3){return true;}
        else if(alive < 2 || alive > 3){
            return false;
        }
    }
    return false;
}

void initializeBoard(std::vector<std::vector<bool>>& change){
    std::vector<std::vector<bool>> ret;
    std::vector<std::pair<int,int>> list;

    std::string input = "";
    std::cout << "Please initiate squares in the following format row,column" << std::endl;
    while(true){
        std::cin >> input;
        if(input == "-1"){break;}
        
        //splits the user input assuming it is perfect for now
        std::pair<int,int> temp;
        temp.first = std::stoi(input.substr(0, input.find(',')));
        temp.second = std::stoi(input.substr(input.find(',') + 1));

        list.push_back(temp);
    }

    for(auto& p : list){
        change[p.first][p.second] = true;
        std::cout << p.first << "," << p.second << std::endl;
    }
}