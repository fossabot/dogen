// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // customers
  //

  inline
  access::object_traits< ::dogen::test_models::northwind::customers >::id_type
  access::object_traits< ::dogen::test_models::northwind::customers >::
  id (const object_type& o)
  {
    return o.customer_id ();
  }

  inline
  void access::object_traits< ::dogen::test_models::northwind::customers >::
  callback (database& db, object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }

  inline
  void access::object_traits< ::dogen::test_models::northwind::customers >::
  callback (database& db, const object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }
}

