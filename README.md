# 🎮 TicTacToe (C++ / SFML 2.6.2)

## 🇵🇱 Opis

Prosta gra kółko i krzyżyk (Tic-Tac-Toe) napisana w języku C++ z wykorzystaniem biblioteki SFML 2.6.2. Projekt skupia się na przejrzystej implementacji logiki gry oraz podstawowej obsłudze grafiki i interakcji użytkownika.

### 🎮 Funkcje

* Proste menu
* Tryb gry: User vs User (lokalnie)
* Tryb gry: User vs AI (algorytm Minimax)
* Automatyczne kopiowanie czcionek podczas budowania projektu
* Wsparcie dla menedżera pakietów Conan

### 🛠️ Technologie

* C++23
* SFML 2.6.2
* Conan

### 📦 Uruchomienie

#### Opcja 1 — Conan (zalecane)

1. Zainstaluj Conan
2. Zainstaluj wymagane zależności:

```bash
conan install . --build=missing
```

3. Skonfiguruj i zbuduj projekt:

```bash
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

4. Uruchom plik wykonywalny

📁 Czcionki są kopiowane automatycznie podczas budowania projektu.

#### Opcja 2 — Ręczna instalacja SFML

1. Zainstaluj SFML 2.6.2
2. Skompiluj projekt (np. g++, MSVC)
3. Uruchom plik wykonywalny

📁 Czcionki są kopiowane automatycznie podczas budowania projektu.

### 📌 Cel projektu

Projekt edukacyjny mający na celu naukę pracy z biblioteką SFML, obsługi zdarzeń oraz implementacji logiki gry.

---

## 🇬🇧 Description

A simple Tic-Tac-Toe game written in C++ using the SFML 2.6.2 library. The project focuses on a clean implementation of game logic and basic handling of graphics and user interaction.

### 🎮 Features

* Simple menu
* Game mode: User vs User (local)
* Game mode: User vs AI (Minimax algorithm)
* Automatic copying of fonts during build
* Conan package manager support

### 🛠️ Technologies

* C++23
* SFML 2.6.2
* Conan

### 📦 Getting Started

#### Option 1 — Conan (recommended)

1. Install Conan
2. Install dependencies:

```bash
conan install . --build=missing
```

3. Configure and build the project:

```bash
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

4. Run the executable

📁 Fonts are copied automatically during the build process.

#### Option 2 — Manual SFML installation

1. Install SFML 2.6.2
2. Compile the project (e.g. g++, MSVC)
3. Run the executable

📁 Fonts are copied automatically during the build process.

### 📌 Purpose

This project was created for educational purposes — to practice working with SFML, event handling, and implementing simple game logic.

---
