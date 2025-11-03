#include <SFML/Graphics.hpp>
#include <array>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode({600, 650}), "Tic Tac Toe - SFML 3.x");

    // Grid lines
    sf::RectangleShape line1({600.f, 5.f}); line1.setPosition({0.f, 200.f}); line1.setFillColor(sf::Color::Black);
    sf::RectangleShape line2({600.f, 5.f}); line2.setPosition({0.f, 400.f}); line2.setFillColor(sf::Color::Black);
    sf::RectangleShape line3({5.f, 600.f}); line3.setPosition({200.f, 0.f}); line3.setFillColor(sf::Color::Black);
    sf::RectangleShape line4({5.f, 600.f}); line4.setPosition({400.f, 0.f}); line4.setFillColor(sf::Color::Black);

    // Font
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return -1;

    // Restart button
    sf::RectangleShape restartButton({200.f, 50.f});
    restartButton.setPosition({200.f, 600.f});
    restartButton.setFillColor(sf::Color(200, 200, 200));
    sf::Text restartText(font, sf::String("Restart"), 30);
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition({230.f, 610.f});

    // Game state
    std::array<std::array<char, 3>, 3> arr;
    char currentPlayer;
    bool gameOver;
    std::string winner;

    // Function to reset the game
    auto resetGame = [&]() {
        char c = '1';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                arr[i][j] = c++;
        currentPlayer = 'X';
        gameOver = false;
        winner = "";
    };
    resetGame();

    // Check winner lambda
    auto checkWinner = [&]() -> std::string {
        for (int i = 0; i < 3; i++) {
            if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) return std::string(1, arr[i][0]);
            if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) return std::string(1, arr[0][i]);
        }
        if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) return std::string(1, arr[0][0]);
        if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) return std::string(1, arr[0][2]);
        return "";
    };

    while (window.isOpen()) {
        while (auto eventOpt = window.pollEvent()) {
            if (!eventOpt) continue;
            auto& event = *eventOpt;

            if (event.is<sf::Event::Closed>()) window.close();

            if (event.is<sf::Event::MouseButtonPressed>()) {
                auto& mouse = *event.getIf<sf::Event::MouseButtonPressed>();
                int mx = mouse.position.x;
                int my = mouse.position.y;

                // Check restart button click
                if (mx >= 200 && mx <= 400 && my >= 600 && my <= 650) {
                    resetGame();
                }

                // Check grid clicks
                if (!gameOver && my < 600) {
                    int row = my / 200;
                    int col = mx / 200;
                    if (arr[row][col] != 'X' && arr[row][col] != 'O') {
                        arr[row][col] = currentPlayer;
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    }
                    winner = checkWinner();
                    if (!winner.empty()) gameOver = true;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(line1); window.draw(line2); window.draw(line3); window.draw(line4);
        window.draw(restartButton);
        window.draw(restartText);

        // Draw X and O
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i][j] == 'X' || arr[i][j] == 'O') {
                    sf::Text text(font, sf::String(std::string(1, arr[i][j])), 120);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition({j * 200 + 50.f, i * 200 + 30.f});
                    window.draw(text);
                }
            }
        }

        // Draw winner text
        if (gameOver) {
            sf::Text endText(font, sf::String("Winner: " + winner), 50);
            endText.setFillColor(sf::Color::Blue);
            endText.setPosition({150.f, 550.f});
            window.draw(endText);
        }

        window.display();
    }

    return 0;
}
