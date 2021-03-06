// quick_sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "node.h"

void add_last(Node* node, int value);
void first_loop(Node* node, Node **sort_start);
void second_loop(Node* node, Node **sort_start);
void switch_to_top(Node* sort_start, Node** to_return);
void clear_memory(Node* node);

int main()
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->m_value = 12;
	node->m_prev = nullptr;
	node->m_next = nullptr;

	add_last(node, 2);
	add_last(node, 3);
	add_last(node, 9);
	add_last(node, 7);
	add_last(node, 0);

	Node* sort_start = nullptr;

	first_loop(node, &sort_start);
	clear_memory(node);
	switch_to_top(sort_start, &sort_start);
	clear_memory(sort_start);
}


void add_last(Node* node, int value)
{
	if (node->m_next == nullptr)
	{
		Node * new_ch = (Node*)malloc(sizeof(Node));
		new_ch->m_prev = node;
		new_ch->m_next = nullptr;
		new_ch->m_value = value;
		node->m_next = new_ch;
		return;
	}
	add_last(node->m_next, value);
}

void first_loop(Node* node, Node** start_sort)
{
	if (node == nullptr)
		return; // tri ok

	second_loop(node, start_sort);

	first_loop(node->m_next, start_sort);
}

void second_loop(Node* node, Node** sort_start)
{
	// between 
	if ((*sort_start) != nullptr && (*sort_start)->m_prev != nullptr && node->m_value > (*sort_start)->m_prev->m_value)
	{
		Node *new_node = (Node*)malloc(sizeof(Node));
		new_node->m_prev = (*sort_start)->m_prev;
		new_node->m_prev->m_next = new_node;
		new_node->m_value = node->m_value;
		new_node->m_next = (*sort_start);
		(*sort_start)->m_prev = new_node;
		return;
	}

	// push on top
	if ((*sort_start) != nullptr && (*sort_start)->m_prev == nullptr) 
	{
		Node *new_node = (Node*)malloc(sizeof(Node));
		new_node->m_next = (*sort_start);
		new_node->m_prev = nullptr;
		new_node->m_value = node->m_value;
		new_node->m_next->m_prev = new_node;
		return;
	}

	if ((*sort_start) != nullptr && (*sort_start)->m_prev == nullptr)
		return;

	//first lap
	if ((*sort_start) == nullptr) 
	{
		Node *new_node = (Node*)malloc(sizeof(Node));
		new_node->m_next = nullptr;
		new_node->m_prev = nullptr;
		new_node->m_value = node->m_value;
		(*sort_start) = new_node;
		return;
	}
	second_loop(node, &(*sort_start)->m_prev);
}

void switch_to_top(Node* sort_start, Node** to_return)
{
	if (sort_start->m_prev == nullptr)
		return;

	(*to_return) = sort_start->m_prev;
	switch_to_top(sort_start->m_prev, to_return);
}

void clear_memory(Node* node)
{
	if(node->m_next == nullptr)
	{
		free(node);
		return;
	}
		
	free(node->m_prev);
	
	clear_memory(node->m_next);
}
