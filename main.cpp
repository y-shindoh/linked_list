/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	main.cpp
 * @brief	連結リストの動作確認コマンド
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#include <cstddef>
#include <cstdio>
#include <set>
#include <cassert>
#include "linked_list.hpp"

/**
 * リストからループの最初のノードを抽出
 * @param[in]	node	処理対象のリスト
 * @return	ループの最初のノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 * @note	直感的な実装。 @a set::set を使う。
 */
template<typename TYPE>
const ys::Node<TYPE>*
FindLoop1(const ys::Node<TYPE>* node)
{
	assert(node);

	std::set<const ys::Node<TYPE>*> nodes;

	while (node) {
		if (nodes.find(node) != nodes.end()) return node;
		nodes.insert(node);
		node = node->get_next();
	}

	return 0;
}

/**
 * リストからループの最初のノードを抽出
 * @param[in]	node	処理対象のリスト
 * @return	ループの最初のノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 * @note	少し考えないと出てこない実装。他構造は不要。
 */
template<typename TYPE>
const ys::Node<TYPE>*
FindLoop2(const ys::Node<TYPE>* node)
{
	assert(node);

	const ys::Node<TYPE>* fast(node);
	const ys::Node<TYPE>* slow(node);

	while ('-') {
		fast = fast->get_next();
		if (!fast) return 0;
		fast = fast->get_next();
		if (!fast) return 0;
		slow = slow->get_next();
		if (fast == slow) break;
	}

	slow = node;

	while ('-') {
		if (fast == slow) return fast;
		fast = fast->get_next();
		slow = slow->get_next();
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
	ys::Node<int>* const list = ys::Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	ys::Node<int>* const tail = ys::Node<int>::GetEndNode(list);
	ys::Node<int>* node(list);
	const ys::Node<int>* loop;

	ys::Node<int>::Print(stdout, list);

	for (size_t i(0); i < 4; ++i) {
		node = node->get_next();
	}
	std::printf("CONNECT: %d\n", node->get_key());

	// ループを作る
	tail->set_next(node);

	loop = FindLoop1<int>(list);
	if (loop) {
		std::printf("FOUND: %d\n", loop->get_key());
	}

	loop = FindLoop2<int>(list);
	if (loop) {
		std::printf("FOUND: %d\n", loop->get_key());
	}

	// ループを切る
	tail->set_next(0);

	ys::Node<int>::DeleteList(list);

	return 0;
}
