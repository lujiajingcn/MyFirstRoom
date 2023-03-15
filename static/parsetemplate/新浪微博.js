function parase_template(element){
	var articleusername = element.querySelector("div > article > div > header > div.woo-box-item-flex.head_main_3DRDm > div > div.woo-box-flex.woo-box-alignCenter.head_nick_1yix2 > a > span");
	var articlecontent = element.querySelector("div > article > div > div > div > div");
	const articleinfo = {
		"articleusername": articleusername.innerText,
		"articlecontent": articlecontent.innerText
	};
	var sarticleinfo = JSON.stringify(articleinfo);
	return sarticleinfo;
}