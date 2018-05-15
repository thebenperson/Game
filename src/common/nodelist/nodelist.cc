/*
 *
 * Game Development Build
 * https://github.com/TheBenPerson/Game
 *
 * Copyright (C) 2016-2018 Ben Stockett <thebenstockett@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stdint.h>
#include <stddef.h>

#include "nodelist.hh"

NodeList::NodeList() {}

NodeList::~NodeList() {

	Node* node;

	while (root) {

		node = root;

		root = node->next;
		delete node;

	}

}

intptr_t NodeList::operator[](unsigned int index) {

	return find(index)->val;

}

void NodeList::add(intptr_t item, unsigned int index) {

	Node *node = new Node();
	node->val = item;

	Timing::lock(&m);

	if (index == UINT_MAX) index = size;

	if (!index) {

		if (!root) last = node;
		else {

			root->prev = node;
			node->next = root;

		}

		root = node;

		size++;
		Timing::unlock(&m);

		return;

	}

	Node *target = find(index - 1);

	node->prev = target;
	node->next = target->next;

	target->next = node;

	if (node->next) node->next->prev = node;
	else last = node;

	size++;
	Timing::unlock(&m);

}

NodeList::Node* NodeList::find(unsigned int index) {

	// todo: cache last node

	Node* node;

	unsigned int i;

	// find most efficient way to cycle
	if ((size - 1 - index) >= index) {

		node = root;

		for (i = 0; i < index; i++)
			node = node->next;

	} else {

		node = last;

		for (i = size - 1; i > index; i--)
			node = node->prev;

	}

	return node;

}

NodeList::Node* NodeList::find(intptr_t item) {

	Node* node = root;

	while (node) {

		if (node->val == item)
			return node;

		node = node->next;

	}

	return NULL;

}

void NodeList::del(Node* node) {

	Timing::lock(&m);

	if (node->prev) node->prev->next = node->next;
	else root = node->next;

	if (node->next) node->next->prev = node->prev;
	if (last == node) last = node->prev;

	delete node;
	size--;

	Timing::unlock(&m);

}

void NodeList::rem(unsigned int index) {

	del(find(index));

}

void NodeList::rem(intptr_t item) {

	del(find(item));

}
