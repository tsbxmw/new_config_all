
set year=%date:~0,4%
echo year=%year%
set month=%date:~5,2%
echo month=%month%
set day=%date:~8,2%
echo day=%day%
set content_fail=δ�ҵ����չ���,�뿪�������ע��
set title_fail=��%project%��%year%-%month%-%day%����--δ�ҵ��汾,�޷����в��ԣ�%ip%
java -jar TestMail.jar %receiver_fail% %title_fail% %content_fail%






