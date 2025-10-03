# 🎮 Josephus Elimination Game - Visual Simulation

<div align="center">

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Raylib](https://img.shields.io/badge/Raylib-8B0000?style=for-the-badge&logo=raylib&logoColor=white)
![DSA](https://img.shields.io/badge/Data_Structures-FF6B6B?style=for-the-badge&logo=data&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-4ECDC4?style=for-the-badge&logo=algorithm&logoColor=white)

**A modern, interactive visualization of the classic Josephus Problem using C++ and Raylib**

[Features](#-features) • [Installation](#-installation) • [How to Play](#-how-to-play) • [Algorithm](#-the-josephus-algorithm) • [Technical Details](#-technical-details)

</div>

---

## 🌟 Features

### 🎨 **Stunning Visual Design**

- **Modern UI**: Beautiful gradient backgrounds with glowing effects
- **Smooth Animations**: Real-time player highlighting and elimination effects
- **Color-Coded Players**: Easy-to-follow visual feedback system
- **High Resolution**: Optimized for 1600x900 display

### 🎮 **Interactive Gameplay**

- **Customizable Settings**: Adjust number of players (3-20) and step count (1-10)
- **Speed Control**: Variable game speed from 10% to 180%
- **Pause/Resume**: Full control over game progression
- **Real-time Updates**: Watch the algorithm work step by step

### 🔧 **Advanced Features**

- **Queue-Based Implementation**: Uses custom templated queue data structure
- **Fullscreen Support**: Toggle between windowed and fullscreen modes
- **Responsive Design**: Adapts to different screen sizes
- **Memory Efficient**: Proper resource management and cleanup

---

## 🚀 Installation

### Prerequisites

- **C++ Compiler**: MinGW-w64 or similar
- **Raylib Library**: Graphics library for C++
- **Make**: Build automation tool

### Quick Setup

1. **Clone the repository**

   ```bash
   git clone https://github.com/YoRu-Cat/Josephus-Game-Raylib-.git
   cd Josephus-Game-Raylib-
   ```

2. **Build the project**

   ```bash
   make
   ```

3. **Run the game**
   ```bash
   ./main.exe
   ```

---

## 🎯 How to Play

### 🎛️ Game Setup

The game starts in setup mode where you can configure the simulation:

| Key     | Action                       | Range        |
| ------- | ---------------------------- | ------------ |
| `↑` `↓` | Adjust number of players     | 3-20 players |
| `←` `→` | Change step count (k)        | 1-10 steps   |
| `Q` `E` | Decrease/Increase game speed | 10%-180%     |
| `ENTER` | Start the elimination game   | -            |

### 🎮 During Gameplay

| Key     | Action            | Description              |
| ------- | ----------------- | ------------------------ |
| `SPACE` | Pause/Resume      | Toggle game progression  |
| `Q` `E` | Speed Control     | Adjust elimination speed |
| `R`     | Reset Game        | Return to setup mode     |
| `F11`   | Toggle Fullscreen | Switch display modes     |
| `ESC`   | Exit              | Close the application    |

### 🎨 Visual Indicators

| Color        | Status         | Description                          |
| ------------ | -------------- | ------------------------------------ |
| 🔵 **Blue**  | Alive Player   | Active participant in the game       |
| 🟢 **Green** | Current Player | Player being counted in current step |
| 🔴 **Red**   | Eliminated     | Player removed from the circle       |
| 🟡 **Gold**  | Winner         | The final survivor                   |

---

## 🧮 The Josephus Algorithm

### 📚 Historical Background

The Josephus problem is a classic theoretical problem in computer science and mathematics. Named after Flavius Josephus, a Jewish historian who lived in the 1st century CE, it describes a choice-based survival scenario.

### 🔄 How It Works

1. **Circle Formation**: N people stand in a circle
2. **Counting Process**: Starting from a designated person, count k positions
3. **Elimination**: The k-th person is eliminated from the circle
4. **Continuation**: Continue counting from the next person
5. **Victory Condition**: The last remaining person is the survivor

### 🎯 Mathematical Formula

For the Josephus problem with n people and step size k, the position of the survivor can be calculated using:

```
J(n,k) = (J(n-1,k) + k) % n
```

With base case: `J(1,k) = 0`

---

## 💻 Technical Details

### 🏗️ Architecture

```
├── Data Structures
│   ├── Custom Queue Implementation (Template-based)
│   ├── Node-based Linked Structure
│   └── Player Management System
├── Game Engine
│   ├── Raylib Graphics Integration
│   ├── Real-time Animation System
│   └── Input Management
└── Algorithm Implementation
    ├── Josephus Logic
    ├── Visual Synchronization
    └── State Management
```

### 🔧 Key Components

#### **Queue Data Structure**

- **Template-based**: Generic implementation for any data type
- **Dynamic Memory**: Efficient memory allocation and deallocation
- **FIFO Operations**: Standard enqueue and dequeue operations
- **Size Tracking**: Real-time queue size monitoring

#### **Game Visualization**

- **Vector Mathematics**: Precise player positioning using trigonometry
- **Color Interpolation**: Smooth color transitions for visual effects
- **Text Rendering**: Dynamic text display with shadows and effects
- **Circle Drawing**: Custom circular layout with proper spacing

#### **Input System**

- **Event-Driven**: Responsive key press detection
- **State-Dependent**: Context-sensitive control schemes
- **Real-time Processing**: Immediate response to user input

### 📊 Performance Characteristics

- **Time Complexity**: O(n×k) for complete simulation
- **Space Complexity**: O(n) for player storage
- **Frame Rate**: Consistent 60 FPS performance
- **Memory Usage**: Minimal footprint with automatic cleanup

---

## 🎮 Game Screenshots

### Setup Phase

```
🎯 JOSEPHUS ELIMINATION GAME

    👤 👤 👤
  👤     👤
👤         👤
  👤     👤
    👤 👤 👤

Players: 9 | Step Count: 2 | Speed: 100%
Press ENTER to start!
```

### Elimination Process

```
🎯 ELIMINATION IN PROGRESS

    👤 ❌ 👤
  👤     🟢
👤         👤
  👤     ❌
    👤 👤 👤

Current Player: 4 | Remaining: 7
```

### Victory Screen

```
🎯 GAME COMPLETE

    👤 ❌ 👤
  ❌     ❌
❌         ❌
  ❌     ❌
    ❌ 🏆 ❌

🏆 WINNER: Player 5 🏆
```

---

## 🔬 Educational Value

### 📖 Learning Objectives

- **Data Structures**: Understanding queue implementation and operations
- **Algorithm Design**: Visualizing recursive and iterative solutions
- **Problem Solving**: Breaking down complex problems into manageable steps
- **Mathematical Modeling**: Connecting theoretical concepts to practical applications

### 🎓 Curriculum Applications

- **Computer Science**: Data structures and algorithms courses
- **Mathematics**: Discrete mathematics and combinatorics
- **Software Engineering**: Object-oriented programming and design patterns
- **Game Development**: Graphics programming and user interface design

---

## 🚀 Advanced Features

### 🎛️ Customization Options

- **Player Range**: Support for 3-20 players
- **Step Variations**: Configurable elimination patterns (k=1 to 10)
- **Speed Control**: Real-time speed adjustment during gameplay
- **Visual Themes**: Modern color schemes with accessibility considerations

### 🔧 Technical Enhancements

- **Memory Management**: Automatic resource cleanup and leak prevention
- **Error Handling**: Robust error checking and graceful degradation
- **Cross-Platform**: Compatible with Windows, Linux, and macOS
- **Modular Design**: Easy to extend and modify

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### 🐛 Bug Reports

- Use the GitHub issue tracker
- Provide detailed reproduction steps
- Include system information

### 💡 Feature Requests

- Suggest new visualization modes
- Propose algorithm optimizations
- Request additional customization options

### 🔧 Code Contributions

- Fork the repository
- Create a feature branch
- Submit a pull request with detailed description

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- **Raylib**: Amazing graphics library that made this visualization possible
- **Flavius Josephus**: For the historical problem that inspired this implementation
- **Computer Science Community**: For continuous algorithm research and education

---

## 📞 Contact

**Developer**: YoRu-Cat  
**Repository**: [Josephus-Game-Raylib-](https://github.com/YoRu-Cat/Josephus-Game-Raylib-)  
**Issues**: [Report Bug](https://github.com/YoRu-Cat/Josephus-Game-Raylib-/issues)

---

<div align="center">

### 🎮 Ready to explore the Josephus Problem?

**[Download Now](https://github.com/YoRu-Cat/Josephus-Game-Raylib-/releases)** | **[View Source](https://github.com/YoRu-Cat/Josephus-Game-Raylib-)** | **[Report Issues](https://github.com/YoRu-Cat/Josephus-Game-Raylib-/issues)**

Made with ❤️ for education and visualization

</div>
