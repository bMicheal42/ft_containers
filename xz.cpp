iterator split_list(List & current)
{
	if (current.size_ == 1) {
		return (current.end());
	}

	Node* fast = current.begin().get_node();
	Node* slow = fast;

	while
			(
			fast != current.end_node_ &&
			fast->next != current.end_node_
			) {
		fast = fast->next->next;
		slow = slow->next;
	}
	if (current.size_ % 2 != 0) {
		slow = slow->next;
	}
	return (iterator(slow));
}

template<class Compare>
void     merge_sort(List & current, Compare comp)
{
	iterator half(split_list(current));
	iterator end(current.end());
	List     new_list(half, end);
	Node*    node;

	while (half != end) {
		node = half.get_node();
		++half;
		destroy_node(node);
		--this->size_;
	}
	if (current.size_ == 1) {
		current.merge(new_list);
		return;
	} else if (current.size_ == 2) {
		Node *node  = current.begin().get_node();
		Node *node2 = node->next;

		if (node->data > node2->data) {
			swap_node(node, node2);
		}
		if (new_list.size_ > 1) {
			new_list.sort(comp);
		}
		current.merge<Compare>(new_list, comp);
		return;
	}
	current.sort<Compare>(comp);
	new_list.sort<Compare>(comp);
	current.merge<Compare>(new_list, comp);
}