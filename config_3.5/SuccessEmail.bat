::������·��
echo server=%server%
::�����汾ǰ׺
echo version_pre=%version_pre%
::����·��
echo local_path=%local_path%
::�ɹ��ҵ����չ���
::����ռ��˷ֺŷָ�
echo receiver_success=%receiver_success%
::�ʼ�����
set title_success=��%project%��%year%-%month%-%day%����--���ҵ��汾��׼����ʼ���ز��ԣ�%ip%
echo title_success=%title_success%
::�ʼ�����
set content_success=�ɹ��ҵ����չ�����
echo content_success=%content_success%

::δ�ҵ����չ���
::����ռ��˷ֺŷָ�
echo receiver_fail=%receiver_fail%
::�ʼ�����
set title_fail=��%project%��%year%-%month%-%day%����--δ�ҵ��汾,�޷����в��ԣ�%ip%
echo title_fail=%title_fail%
::�ʼ�����
set content_fail=δ�ҵ����չ���,�뿪�������ע��
echo content_fail=%content_fail%
::���ذ汾�ļ�
set local_version_file=E:\version\P809V50\P809V50.zip
echo local_version_file=%local_version_file%
if exist %local_version_file% (
echo download over!
echo A | "C:\Program Files\HaoZip\HaoZipC.exe" e E:\version\P809V50\P809V50.zip -o%local_path%

java -jar TestMail.jar %receiver_success% %title_success% %content_success%
) else (
   java -jar TestMail.jar %receiver_fail% %title_fail% %content_fail%
    )

    
goto :eof

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::	�ӳ�����ʱ
::		��ʱ����Ϊ ����*10��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:DELAY
for /l %%Z in (%1,-1,0) do (ping 10.0.0.127 -w 10000 -n 1 >nul)
goto :eof

pause