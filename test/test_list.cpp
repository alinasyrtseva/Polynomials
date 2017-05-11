#include "List.h"

#include <gtest/gtest.h>

// Тестирование класса Список

TEST (List, can_create_list_with_positive_length)
{
	ASSERT_NO_THROW (List <int> l (1));
}

TEST (List, can_create_empty_list)
{
	ASSERT_NO_THROW (List <int> l);
}

TEST (List, throws_when_create_list_with_negative_length)
{
	ASSERT_ANY_THROW (List <int> l (-1));
}

TEST (List, can_get_size)
{
	List <int> l (10);

	ASSERT_EQ (10, l.GetSize());
}

TEST (List, can_determine_if_list_is_empty)
{
	List <int> l (10);

	ASSERT_EQ (0, l.IsEmpty());
}

TEST (List, can_insert_in_the_head)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheHead (7);

	EXPECT_EQ (7, l.ViewHeadData ());
}

TEST (TList, can_insert_in_empty_list)
{
	List <int> l;

	ASSERT_NO_THROW (l.InsertInTheHead (5));
}

TEST (List, insert_in_the_head_is_accompanied_by_a_change_in_size)
{
	List <int> l (10);
	l.InsertInTheHead (5);

	ASSERT_EQ (11, l.GetSize());
}

TEST (List, can_insert_in_the_tail)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);

	EXPECT_EQ (7, l.ViewTailData ());
}

TEST (List, insert_in_the_tail_is_accompanied_by_a_change_in_size)
{
	List <int> l (10);
	l.InsertInTheTail (5);

	ASSERT_EQ (11, l.GetSize());
}

TEST (List, can_insert_after_pointer)
{
	List <int> l;
	l.InsertInTheHead (5);
	Node <int> * ptr = l.SearchByKey (5);
	l.InsertAfterPointer (7, ptr);

	EXPECT_EQ (7, l.ViewPointerData (l.SearchByKey (7)));
}

TEST (List, insert_after_pointer_is_accompanied_by_a_change_in_size)
{
	List <int> l;
	l.InsertInTheHead (5);
	Node <int> * ptr = l.SearchByKey (5);
	l.InsertAfterPointer (7, ptr);

	ASSERT_EQ (2, l.GetSize ());
}

//TEST(List, can_remove_from_the_head)
//{
//	List <int> l;
//	l.InsertInTheHead (5);
//	l.InsertInTheHead (7);
//	int top = l.RemoveFromTheHead ();
//	
//	EXPECT_EQ (5, l.ViewHeadData ());
//}

//TEST (List, throws_when_remove_from_the_head_of_an_empty_list)
//{
//	List <int> l;
//
//	ASSERT_ANY_THROW (int top = l.RemoveFromTheHead ());
//}

TEST(List, can_remove_from_the_tail)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);
	l.RemoveFromTheTail ();
	
	EXPECT_EQ (5, l.ViewTailData ());
}

TEST (List, throws_when_remove_from_the_tail_of_an_empty_list)
{
	List <int> l;

	ASSERT_ANY_THROW (l.RemoveFromTheTail ());
}

TEST (List, remove_from_the_tail_is_accompanied_by_a_change_in_size)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);
	l.RemoveFromTheTail ();

	ASSERT_EQ (1, l.GetSize());
}

TEST(List, can_remove_after_pointer)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);
	Node <int> * ptr = l.SearchByKey (5);
	l.RemoveAfterPointer (ptr);

	ASSERT_EQ (5, l.ViewTailData ());
}

//TEST (List, throws_when_remove_after_pointer_of_an_empty_list)
//{
//	List <int> l;
//	l.InsertInTheHead (5);
//	Node <int> * ptr = l.SearchByKey (5);
//	int top = l.RemoveFromTheHead ();
//
//	ASSERT_ANY_THROW (l.RemoveAfterPointer (ptr));
//}


TEST (List, remove_after_pointer_is_accompanied_by_a_change_in_size)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);
	Node <int> * ptr = l.SearchByKey (5);
	l.RemoveAfterPointer (ptr);

	ASSERT_EQ (1, l.GetSize());
}

TEST (List, can_search_by_key)
{
	List <int> l;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);
	Node <int> * ptr = l.SearchByKey (7);

	EXPECT_EQ (7, ptr -> Data);
}

TEST (List, cant_search_by_key_in_empty_list)
{
	List <int> l;

	ASSERT_ANY_THROW (l.SearchByKey (5));
}


TEST (List, can_copy)
{
	List <int> l, m;
	l.InsertInTheHead (5);
	l.InsertInTheTail (7);

	ASSERT_NO_THROW (m = l);
}