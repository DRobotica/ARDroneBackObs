/* Auto-generated by genmsg_cpp for file /home/jesus/ros_workspace/sandbox/beginner_tutorials/msg/Num.msg */
#ifndef BEGINNER_TUTORIALS_MESSAGE_NUM_H
#define BEGINNER_TUTORIALS_MESSAGE_NUM_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace beginner_tutorials
{
template <class ContainerAllocator>
struct Num_ {
  typedef Num_<ContainerAllocator> Type;

  Num_()
  : num(0)
  {
  }

  Num_(const ContainerAllocator& _alloc)
  : num(0)
  {
  }

  typedef int64_t _num_type;
  int64_t num;


  typedef boost::shared_ptr< ::beginner_tutorials::Num_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::beginner_tutorials::Num_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Num
typedef  ::beginner_tutorials::Num_<std::allocator<void> > Num;

typedef boost::shared_ptr< ::beginner_tutorials::Num> NumPtr;
typedef boost::shared_ptr< ::beginner_tutorials::Num const> NumConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::beginner_tutorials::Num_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::beginner_tutorials::Num_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace beginner_tutorials

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::beginner_tutorials::Num_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::beginner_tutorials::Num_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "57d3c40ec3ac3754af76a83e6e73127a";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x57d3c40ec3ac3754ULL;
  static const uint64_t static_value2 = 0xaf76a83e6e73127aULL;
};

template<class ContainerAllocator>
struct DataType< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "beginner_tutorials/Num";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int64 num\n\
\n\
";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::beginner_tutorials::Num_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::beginner_tutorials::Num_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.num);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Num_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::beginner_tutorials::Num_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::beginner_tutorials::Num_<ContainerAllocator> & v) 
  {
    s << indent << "num: ";
    Printer<int64_t>::stream(s, indent + "  ", v.num);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BEGINNER_TUTORIALS_MESSAGE_NUM_H

