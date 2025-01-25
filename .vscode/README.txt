sql

select
select para1 operator integer (and para2 operator integer);

operator : 
bt - better than
ebt - equal to or better than
eq - equal
lt - less than
elt - equal to or better than

insert
insert number nameVal hpVal atkVal defVal spaVal spdVal spdVal;

update
update number para1 : %d, ... , paraN : %d;

delete
delete number;

//exe 파일 인코딩
$OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = [System.Text.Encoding]::UTF8
.\main.exe