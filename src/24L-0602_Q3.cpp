#include <iostream>
using namespace std;

// Player structure to track alive/dead status
struct Player
{
  int position;
  bool dead;

  Player(int pos = 0)
  {
    position = pos;
    dead = false;
  }
};

template <typename T>
class Node
{
public:
  T data;
  Node<T> *next;

  Node(const T &val)
  {
    data = val;
    next = nullptr;
  }
};

template <typename T>
class Queue
{
private:
  Node<T> *front;
  Node<T> *rear;
  int size;

public:
  Queue()
  {
    front = nullptr;
    rear = nullptr;
    size = 0;
  }

  ~Queue()
  {
    while (!isEmpty())
    {
      dequeue();
    }
  }

  bool isEmpty()
  {
    return front == nullptr;
  }

  void enqueue(const T &val)
  {
    Node<T> *newNode = new Node<T>(val);
    if (isEmpty())
    {
      front = rear = newNode;
    }
    else
    {
      rear->next = newNode;
      rear = newNode;
    }
    size++;
  }

  T dequeue()
  {
    if (isEmpty())
    {
      cout << "Queue is empty!" << endl;
      return T();
    }

    Node<T> *temp = front;
    T data = front->data;
    front = front->next;

    if (front == nullptr)
    {
      rear = nullptr;
    }

    delete temp;
    size--;
    return data;
  }

  T getFront()
  {
    if (isEmpty())
    {
      cout << "Queue empty!" << endl;
      return T();
    }
    return front->data;
  }

  int getSize()
  {
    return size;
  }
};

class JosephusQueue
{
private:
  Queue<Player> circle;
  int totalPlayers;
  int alivePlayers;

public:
  JosephusQueue()
  {
    totalPlayers = 0;
    alivePlayers = 0;
  }

  void create(int N)
  {
    totalPlayers = N;
    alivePlayers = N;

    // N players ko queue mein add karte hain
    for (int i = 1; i <= N; i++)
    {
      Player p(i);
      circle.enqueue(p);
    }

    cout << N << " players added to circle!" << endl;
  }

  int solveJosephus(int k)
  {
    if (circle.isEmpty())
    {
      cout << "No players available!" << endl;
      return -1;
    }

    cout << "\n=== Josephus Game Start ===" << endl;
    cout << "Every " << k << " steps, one player will be eliminated" << endl
         << endl;

    int step = 1;

    while (alivePlayers > 1)
    {
      Player current = circle.dequeue();

      if (!current.dead)
      {
        if (step == k)
        {
          // Is player ko eliminate karte hain
          current.dead = true;
          alivePlayers--;

          cout << "Step " << k << ": Player " << current.position << " eliminated!" << endl;
          cout << "Remaining players: " << alivePlayers << endl
               << endl;

          step = 1; // Reset counter
        }
        else
        {
          step++;
        }
      }

      // Player ko wapas queue mein daal dete hain (dead/alive status ke saath)
      circle.enqueue(current);
    }

    // Bas ek zinda player bach gaya hai - use dhundte hain
    while (!circle.isEmpty())
    {
      Player p = circle.dequeue();
      if (!p.dead)
      {
        return p.position;
      }
    }

    return -1;
  }

  void displayCircle()
  {
    if (circle.isEmpty())
    {
      cout << "Circle is empty!" << endl;
      return;
    }

    cout << "Current circle status:" << endl;
    Queue<Player> temp;

    // Sabko dequeue kar ke check karte hain
    while (!circle.isEmpty())
    {
      Player p = circle.dequeue();
      cout << "Player " << p.position;
      if (p.dead)
      {
        cout << " (DEAD)";
      }
      else
      {
        cout << " (ALIVE)";
      }
      cout << " -> ";
      temp.enqueue(p);
    }
    cout << "..." << endl;

    // Wapas original queue mein daal dete hain
    while (!temp.isEmpty())
    {
      circle.enqueue(temp.dequeue());
    }
  }
};

int console_main()
{
  int N, k;

  cout << "=== Josephus Problem using Queue ===" << endl;
  cout << "Number of people (N): ";
  cin >> N;
  cout << "Step count (k): ";
  cin >> k;

  JosephusQueue jq;
  jq.create(N);

  int survivor = jq.solveJosephus(k);

  cout << "=== RESULT ===" << endl;
  cout << "Last survivor: Player " << survivor << endl;

  return 0;
}