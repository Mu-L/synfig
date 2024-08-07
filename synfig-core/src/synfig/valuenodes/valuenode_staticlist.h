/* === S Y N F I G ========================================================= */
/*!	\file valuenode_staticlist.h
**	\brief Header file for implementation of the "StaticList" valuenode conversion.
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**
**	This file is part of Synfig.
**
**	Synfig is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 2 of the License, or
**	(at your option) any later version.
**
**	Synfig is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with Synfig.  If not, see <https://www.gnu.org/licenses/>.
**	\endlegal
*/
/* ========================================================================= */

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_VALUENODE_STATICLIST_H
#define __SYNFIG_VALUENODE_STATICLIST_H

/* === H E A D E R S ======================================================= */

#include <vector>

#include <synfig/uniqueid.h>
#include <synfig/valuenode.h>

/* === M A C R O S ========================================================= */

/* === C L A S S E S & S T R U C T S ======================================= */

namespace synfig {
class Canvas;

/*! \class ValueNode_StaticList
**	\brief StaticList ValueNode
**
**	This ValueNode is set up to have a list of ValueNodes.
*/
class ValueNode_StaticList : public LinkableValueNode
{
	Type *container_type;
	bool loop_;

protected:
	ValueNode_StaticList(Type &container_type=type_nil, etl::loose_handle<Canvas> canvas = 0);

public:
	typedef etl::handle<ValueNode_StaticList> Handle;
	typedef etl::handle<const ValueNode_StaticList> ConstHandle;
	typedef ValueNode::Handle ListEntry;
	typedef ValueNode::RHandle ReplaceableListEntry;

	std::vector<ReplaceableListEntry> list;

	static ValueNode_StaticList* create(const ValueBase& x=type_gradient, etl::loose_handle<Canvas> canvas=nullptr);
	virtual ValueNode::Handle clone(etl::loose_handle<Canvas> canvas, const GUID& deriv_guid=GUID()) const override;
	virtual ~ValueNode_StaticList();

	virtual String get_name() const override;
	virtual String get_local_name() const override;
	static bool check_type(Type &type);

	virtual int link_count() const override;
	virtual String link_local_name(int i) const override;
	virtual String link_name(int i) const override;
	virtual int get_link_index_from_name(const String &name) const override;

	virtual ValueBase operator()(Time t) const override;

	virtual ListEntry create_list_entry(int index, Time time=0, Real origin=0.5);

protected:
	LinkableValueNode* create_new() const override;

	virtual bool set_link_vfunc(int i,ValueNode::Handle x) override;
	virtual ValueNode::LooseHandle get_link_vfunc(int i) const override;

	virtual Vocab get_children_vocab_vfunc() const override;

public:
	/*! \note The construction parameter (\a type) is the type that the list
	**	contains, rather than the type that it will yield
	**	(which is type_list)
	*/
	static Handle create_on_canvas(Type &type=type_nil, etl::loose_handle<Canvas> canvas = 0);

	void add(const ValueNode::Handle &value_node, int index=-1);
	void erase(const ListEntry &value_node);
//	void reindex();

	bool get_loop() const { return loop_; }
	void set_loop(bool x) { loop_=x; }

	void set_member_canvas(etl::loose_handle<Canvas>);

	Type& get_contained_type() const;

	// TODO: better type-checking
	template <typename iterator> static Handle
	create_from_list(iterator begin, iterator end)
	{
		Handle ret = create_on_canvas((*begin)->get_type());
		for(;begin!=end;++begin)
			ret->add(*begin);
		return ret;
	}

//	void insert_time(const Time& location, const Time& delta);

#ifdef _DEBUG
	void ref() const noexcept override;
	void unref() const override;
#endif

}; // END of class ValueNode_StaticList

}; // END of namespace synfig

/* === E N D =============================================================== */

#endif
