/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	linked_list.hpp
 * @brief	連結リスト
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#ifndef	__LINKED_LIST_HPP__
#define	__LINKED_LIST_HPP__ "linked_list.hpp"

//#define	USE_DOUBLY_LINKED_LIST	"use doubly linked list."

#include <cstddef>
#include <cstdio>
#include <cassert>

namespace ys
{
	/**
	 * @class	連結リストのノード
	 * @note	テンプレートの型 @a TYPE はリストのキーの型。
	 */
	template<typename TYPE>
	class Node
	{
	private:

		TYPE key_;				///< ノードのキー
#ifdef	USE_DOUBLY_LINKED_LIST
		Node<TYPE>* previous_;	///< 前のノード (前がなければ @a 0 )
#endif	// USE_DOUBLY_LINKED_LIST
		Node<TYPE>* next_;		///< 次のノード (次がなければ @a 0 )

	public:

#ifdef	USE_DOUBLY_LINKED_LIST
		/**
		 * コンストラクタ
		 * @param[in]	key	ノードのキー
		 */
		Node(const TYPE& key,
			 Node<TYPE>* previous = 0,
			 Node<TYPE>* next = 0)
			: key_(key), previous_(previous), next_(next)
			{
				;
			}
#else	// USE_DOUBLY_LINKED_LIST
		/**
		 * コンストラクタ
		 * @param[in]	key	ノードのキー
		 */
		Node(const TYPE& key,
			 Node<TYPE>* next = 0)
			: key_(key), next_(next)
			{
				;
			}
#endif	// USE_DOUBLY_LINKED_LIST

		/**
		 * デストラクタ
		 */
		~Node()
			{
				;
			}

		/**
		 * キーの設定
		 * @param[in]	ノードのキー
		 */
		void
		set_key(const TYPE& key)
			{
				key_ = key;
			}

		/**
		 * キーの取得
		 * @return	ノードのキー
		 */
		TYPE
		get_key() const
			{
				return key_;
			}

#ifdef	USE_DOUBLY_LINKED_LIST
		/**
		 * 前のノードの設定
		 * @param[in]	前のノード
		 */
		void
		set_previous(Node<TYPE>* node)
			{
				previous_ = node;
			}

		/**
		 * 前のノードの取得
		 * @return	前のノード
		 */
		Node<TYPE>*
		get_previous() const
			{
				return previous_;
			}
#endif	// USE_DOUBLY_LINKED_LIST

		/**
		 * 次のノードの設定
		 * @param[in]	次のノード
		 */
		void
		set_next(Node<TYPE>* node)
			{
				next_ = node;
			}

		/**
		 * 次のノードの取得
		 * @return	次のノード
		 */
		Node<TYPE>*
		get_next() const
			{
				return next_;
			}

		/**
		 * リストを生成
		 * @param[in]	keys	リストに含める値の配列
		 * @param[in]	length	引数 @a keys の長さ
		 * @return	生成したリストの先頭ノード
		 * @note	計算量はΘ(n)。ただしnは配列の長さ。
		 */
		static Node<TYPE>*
		MakeList(const TYPE* keys,
				 size_t length)
			{
				assert(keys);

				Node<TYPE>* head(0);
				Node<TYPE>* previous(0);
				Node<TYPE>* current;

				for (size_t i(0); i < length; ++i) {
					current = new Node<TYPE>(keys[i]);
					if (previous) {
#ifdef	USE_DOUBLY_LINKED_LIST
						current->set_previous(previous);
#endif	// USE_DOUBLY_LINKED_LIST
						previous->set_next(current);
					}
					if (!head) head = current;
					previous = current;
				}

				return head;
			}

		/**
		 * リストを削除
		 * @param[in]	head	リストの先頭ノード
		 * @note	計算量はΘ(n)。ただしnはリストの長さ。
		 */
		static void
		DeleteList(Node<TYPE>* head)
			{
				Node<TYPE>* current(head);
				Node<TYPE>* next;

				while (current) {
					next = current->get_next();
					delete current;
					current = next;
				}
			}

		/**
		 * リストの末尾ノードを取得
		 * @param[in]	head	リストの先頭ノード
		 * @return	リストの末尾ノード
		 * @note	計算量はΘ(n)。ただしnはリストの長さ。
		 */
		static Node<TYPE>*
		GetEndNode(Node<TYPE>* node)
			{
				assert(node);

				while (node->get_next()) {
					node = node->get_next();
				}

				return node;
			}

		/**
		 * リストの末尾ノードを取得
		 * @param[in]	head	リストの先頭ノード
		 * @return	リストの末尾ノード
		 * @note	計算量はΘ(n)。ただしnはリストの長さ。
		 */
		static const Node<TYPE>*
		GetEndNode(const Node<TYPE>* node)
			{
				assert(node);

				while (node->get_next()) {
					node = node->get_next();
				}

				return node;
			}

		/**
		 * リスト (ノード列) を出力
		 * @param[out]	file	出力
		 * @param[in]	node	リストの先頭ノード
		 */
		static void
		Print(FILE* file,
			  const Node<TYPE>* node)
			{
				bool first(true);

				std::fprintf(file, "[");

				while (node) {
					if (!first) std::fprintf(file, "->");
					std::fprintf(file, "%G", (double)node->get_key());
					node = node->get_next();
					first = false;
				}

				std::fprintf(file, "]\n");
			}
	};
};

#endif	// __LINKED_LIST_HPP__
