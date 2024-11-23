mixed-port: 7890
allow-lan: true
bind-address: '*'
mode: rule              #规则模式 rule 全局模式 global
log-level: info
external-controller: '127.0.0.1:9090'

dns:
   enable: true
   default-nameserver:
     - 1.1.1.1
   nameserver:
     - https://1.1.1.1/dns-quer
   fallback:
     - https://1.1.1.1/dns-query
   fallback-filter:
     geoip: true
     geoip-code: CN
     ipcidr:
      - 240.0.0.0/4
      
proxies:
  - # A1
    type: vless
    name: pages - 01
    server: 104.19.197.79
    servername: x.com
    uuid: aA123
    client-fingerprint: chrome
    flow: xtls-rprx-vision
    port: 443
    tls: true
    udp: true
    network: ws
    sni: x.com
    ws-opts:
      headers:
        host: x.com
      path: /?ed=2048
    alpn:
      - h2
  - # A2
    type: vless
    name: pages - 02
    server: 104.18.81.12
    servername: x.com
    uuid: aA123
    client-fingerprint: chrome
    flow: xtls-rprx-vision
    port: 443
    tls: true
    udp: true
    network: ws
    sni: x.com
    ws-opts:
      headers:
        host: x.com
      path: /?ed=2048
    alpn:
      - h2
proxy-groups:
    - { name: PROXY, type: select, proxies: [pages - 01, pages - 02] }
rule-providers:
    # 广告屏蔽
    reject:
      type: http
      behavior: domain
      url: "https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/reject.txt"
      path: ./ruleset/reject.yaml
      interval: 86400
    # 国内域名
    direct:
      type: http
      behavior: domain
      url: "https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/direct.txt"
      path: ./ruleset/direct.yaml
      interval: 86400
    # 国内IP
    cncidr:
      type: http
      behavior: ipcidr
      url: "https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/cncidr.txt"
      path: ./ruleset/cncidr.yaml
      interval: 86400
    # 局域网
    lancidr:
      type: http
      behavior: ipcidr
      url: "https://cdn.jsdelivr.net/gh/Loyalsoldier/clash-rules@release/lancidr.txt"
      path: ./ruleset/lancidr.yaml
      interval: 86400
rules:
    # openAI语言大模型
    - 'DOMAIN-KEYWORD,openai,ChatGPT'
    - 'DOMAIN-SUFFIX,auth0.com,ChatGPT'
    - 'DOMAIN-SUFFIX,challenges.cloudflare.com,ChatGPT'
    - 'DOMAIN-SUFFIX,chatgpt.com,ChatGPT'
    - 'DOMAIN-SUFFIX,client-api.arkoselabs.com,ChatGPT'
    - 'DOMAIN-SUFFIX,events.statsigapi.net,ChatGPT'
    - 'DOMAIN-SUFFIX,featuregates.org,ChatGPT'
    - 'DOMAIN-SUFFIX,identrust.com,ChatGPT'
    - 'DOMAIN-SUFFIX,intercom.io,ChatGPT'
    - 'DOMAIN-SUFFIX,intercomcdn.com,ChatGPT'
    - 'DOMAIN-SUFFIX,oaistatic.com,ChatGPT'
    - 'DOMAIN-SUFFIX,oaiusercontent.com,ChatGPT'
    - 'DOMAIN-SUFFIX,openai.com,ChatGPT'
    - 'DOMAIN-SUFFIX,openaiapi-site.azureedge.net,ChatGPT'
    - 'DOMAIN-SUFFIX,sentry.io,ChatGPT'
    - 'DOMAIN-SUFFIX,stripe.com,ChatGPT'
    # 其它规则
    - 'RULE-SET,reject,REJECT'
    - 'RULE-SET,direct,DIRECT'
    - 'RULE-SET,cncidr,DIRECT'
    - 'RULE-SET,lancidr,DIRECT'
    - 'MATCH,PROXY'
