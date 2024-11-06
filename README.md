# 💻 Minishell

[![License](https://img.shields.io/github/license/Disaster-Loki/Minishell?color=blue)](./LICENSE)
[![Contributors](https://img.shields.io/github/contributors/Disaster-Loki/Minishell)](https://github.com/Disaster-Loki/Minishell/graphs/contributors)
[![Stars](https://img.shields.io/github/stars/Disaster-Loki/Minishell?style=social)](https://github.com/Disaster-Loki/Minishell/stargazers)

A project to develop a minishell in C, replicating the basic behavior of a Unix terminal.

## 📚 Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Collaborators](#collaborators)
- [License](#license)

## 📖 About the Project
The **Minishell** project aims to build a simple Unix-like shell in C. This shell handles basic commands, process execution, and signal management, simulating some of the essential functionalities of popular Unix shells like Bash.

## ✨ Features
- **Command Execution**: Supports executing common Unix commands.
- **Built-in Commands**: Includes commands like `cd`, `echo`, `exit`, `env`, `unset`, etc.
- **Piping**: Ability to connect commands through pipes.
- **Signal Handling**: Handles signals like `Ctrl+C` and `Ctrl+D`.
- **Environment Variable Management**: Allows managing environment variables.

## 🤝 Collaborators
This project is developed by:

- [Disaster-Loki](https://github.com/Disaster-Loki)
- [ptchipoc](https://github.com/ptchipoc)
  
## ⚙️ Installation
To install and set up the Minishell project, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Disaster-Loki/Minishell.git
    ```

2. **Navigate to the project directory**:
    ```bash
    cd Minishell
    ```

3. **Compile the shell**:
    ```bash
    make
    ```

## 🚀 Usage
Once compiled, you can start the Minishell by running:
```bash
./minishell
