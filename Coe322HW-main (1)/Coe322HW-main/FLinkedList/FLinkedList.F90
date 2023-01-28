!Antonio Jimenez aoj268 
!Ceci Nguyen dcn558

Program LinkedList

  implicit none
  type node
     integer :: value
     type(node),pointer :: next
  end type node

  type list
     type(node),pointer :: head
  end type list
  
  integer,parameter :: listsize = 7
  type(list) :: the_list
  integer :: input,input_value,i

  nullify(the_list%head)
  do i=1,listsize
     read *, input_value
     call insert(the_list,input_value)
!     print *,"|list| = ",length(the_list)
     call print(the_list)
  end do
contains
  subroutine insert(the_list, new_value)
    implicit none
    ! parameters
    type(list),intent(inout) :: the_list
    integer,intent(in) :: new_value
    type(node), pointer :: current_node, new_node, holder
    integer :: pos
    ! local
    !allocate(current_node)
! if the list has no head node, attached the new node
    if (.not.associated(the_list%head)) then
       allocate( the_list%head )
       the_list%head%value = new_value
! new node becomes head node, if smaller than head node.
    else if (new_value .lt. the_list%head%value) then
       allocate (new_node)
       new_node%value = new_value
       new_node%next => the_list%head 
       the_list%head => new_node
    else 
       current_node => the_list%head
       pos = 1      
       do while( associated(current_node%next) )
          allocate (new_node)
             new_node%value = new_value
          if (new_value .eq. current_node%value) then 
             Print *, 'Already in the list'
             exit
          else if (new_value .lt. current_node%value) then!cant occur would have been caught by < head
             Print *, "Cant Happen"
             exit 
          else if (new_value .lt. current_node%next%value .and. new_value .gt. current_node%value) then!automatically assumed it is greater than current node
             new_node%next => current_node%next!65 points to 73
             current_node%next => new_node !62 points to 65
             exit 
             
          else if (new_value .gt. current_node%value) then!assumed it is also not less than next node
             current_node => current_node%next
             pos = pos + 1
        
          else
             Print *, "We missed a case"
          end if
       end do
       if (.not. associated(current_node%next)) then
          allocate(current_node%next) ! if it is the largest in the list
          current_node%next%value = new_value
       end if
    end if
  end subroutine insert
      
!  end subroutine attach
  

  integer function length( the_list )
    implicit none
    type(list),intent(in),target :: the_list
    ! local
    type(node),pointer :: current

    length = 0
    current => the_list%head
    if ( associated(current) ) then
       do while( associated(current%next) )
          length = length+1
          !print *,current%value
          current => current%next
       end do
    end if

  end function length

  subroutine print(the_list)
    implicit none
    type(list),intent(in) :: the_list
    type(node),pointer :: current

    write(*,'("List: [ ")',advance="no")
    if (associated(the_list%head)) then
       current => the_list%head
       do while (associated(current))
          write(*,'(i0",")',advance="no") current%value
          if (.not.associated(current%next)) exit
          current => current%next
       end do
    end if
    write(*,'(x"]")')

  end subroutine print
  
end Program LinkedList
