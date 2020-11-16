#!/bin/bash
grep -r @url | sed "s/\r//g" | awk '{if($4!="") print $1}' | awk -F : '{if($1!="post.sh") print $1}' > list.txt

res=`curl -X POST -d "email=${email}" -d "password=${password}" --dump-header - https://api.ningenme.net/v1/login | grep x-amzn-remapped-authorization:`
header=`echo $res | awk -F : '{print $2}'`

header1="\"authorization: "${header}\"
header2="\"Content-Type: application/json\""
host="https://api.ningenme.net/v1/compro/category/tasks"

cat list.txt | while read line
do
  file=$line
  url=`cat $file | sed "s/\r//g" | egrep '@url' | awk '{print $3}'`
  est=`cat $file | sed "s/\r//g" | egrep '@est' | awk '{print $3}'`
  json="'"{\"url\":\"$url\",\"estimation\":\"$est\",\"topicIdList\":[\"266\"]}"'"

  header1=`echo $header1 | sed "s/\r//g"`
  header2=`echo $header2 | sed "s/\r//g"`
  json=`echo $json    | sed "s/\r//g"`
  
  curl="curl -X POST -H ${header1} -H ${header2} -d $json $host"
  eval ${curl}
  echo $url
done

