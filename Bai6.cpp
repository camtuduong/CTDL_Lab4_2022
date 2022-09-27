#include <iostream>

#define MAX 100

using namespace std;

typedef struct BenhNhan
{
    string name;
    int age;
} BN;

BN input()
{
    BN bn;
    cout << "Nhap name: " << endl;
    cin >> bn.name;
    cout << "Nhap tuoi: " << endl;
    cin >> bn.age;
    return bn;
}

void output(BN benhNhan)
{
    cout << "\nTen ben nhan: " << benhNhan.name << "\nTuoi benh nhan: " << benhNhan.age;
}

typedef struct queue
{
    BN data[MAX];
    int front = 0;
    int rear = 0;
    int length = 0;
    int deleted = 0;

} Queue;

bool isEmpty(Queue queue)
{
    return queue.length == 0;
}

bool isFull(Queue queue)
{
    return queue.length == MAX;
}

BN getFront(Queue queue)
{
    return queue.data[queue.front];
}

BN popFront(Queue &queue)
{
    queue.length--;
    queue.deleted++;
    return queue.data[(queue.front-- + MAX) % MAX];
}

bool pushBack(Queue &queue, BN data)
{
    if (isFull(queue))
        return false;
    queue.length++;
    queue.data[queue.front++ % MAX] = data;
    return true;
}

void printQueue(Queue queue)
{
    for (int i = 0; i < queue.length; i++)
    {
        output(queue.data[(queue.rear + i) % MAX]);
        printf("\n");
    }
}

int main()
{
    Queue queue;
    for (int i = 0; i < 3; i++)
        // Them benh nhan
        pushBack(queue, input());
    // Lay benh nhan tiep theo
    BN benhNhan;
    benhNhan = popFront(queue);
    // So luong nguoi da kham
    cout << "Da kham: " << queue.deleted << endl;
    // Chua kham
    cout << "Chua kham: " << queue.length << endl;
    // Danh sach chua kham
    printQueue(queue);
    return 0;
}
