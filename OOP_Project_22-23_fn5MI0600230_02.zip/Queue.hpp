#pragma once

#include <iostream>
#include <exception>
template <typename T>
class Queue
{
	T* data;
	size_t capacity;
	size_t size;

	size_t get;
	size_t put;

	void resize();

	void moveFrom(Queue<T>&& other);
	void copyFrom(const Queue<T>& other);
	void free();
public:
	Queue();

	const T& front() const;

	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	Queue(Queue<T>&& other);
	Queue<T>& operator=(Queue<T>&& other);

	void push(const T& obj);
	void push(T&& obj);
	void pop();

	const T& peek() const;
	bool isEmpty() const;

	~Queue();

};

template <typename T>
const T& Queue<T>::front() const
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");

	return data[get];
}

template <typename T>
Queue<T>::Queue()
{
	capacity = 4;
	data = new T[capacity];
	size = 0;
	get = put = 0;
}

template <typename T>
void Queue<T>::push(const T& obj)
{
	if (size == capacity)
		resize();

	data[put] = obj; //operator=
	(++put) %= capacity;
	size++;
}

template <typename T>
void Queue<T>::push(T&& obj)
{
	if (size == capacity)
		resize();

	data[put] = std::move(obj); //move operator =
	(++put) %= capacity;
	size++;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	return size == 0;
}


template <typename T>
const T& Queue<T>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");

	return data[get];
}

template <typename T>
void Queue<T>::pop()
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");
	(++get) %= capacity;
	size--;
}

template <typename T>
void Queue<T>::resize()
{
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++)
	{
		resizedData[i] = data[get];
		(++get) %= capacity;
	}
	capacity *= 2;
	delete[] data;
	data = resizedData;
	get = 0;
	put = size;
}


template <typename T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
	data = new T[other.capacity];
	for (int i = 0; i < other.capacity; i++)
		data[i] = other.data[i];

	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

}

template <typename T>
void Queue<T>::moveFrom(Queue<T>&& other)
{
	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;

	other.size = other.capacity = 0;
}

template <typename T>
void Queue<T>::free()
{
	delete[] data;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other)
{
	copyFrom(other);

}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


template <typename T>
Queue<T>::~Queue()
{
	free();
}
