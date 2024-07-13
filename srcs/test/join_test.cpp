	/* Test if _channels and _client_chan are correctly filled */
	std::cout << std::endl; 
	std::cout << "Test the channel name from JOIN:\n" << std::endl;
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		std::cout << "Chan name: " << _channels[i]->get_chan_name() << std::endl;
		std::cout << "Chan key: " << _channels[i]->get_key() << std::endl;
		std::vector<Client*> cpy_client_chan = _channels[i]->get_clients_of_chan();
		std::cout << "cpy_client_chan.size(): " << cpy_client_chan.size() << std::endl;
		std::cout << "Client belong to the channel:" << std::endl;
		for (size_t j = 0; j <  cpy_client_chan.size(); ++j)
        	std::cout << "Client: " << cpy_client_chan[j]->get_nickname() << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << "Channels belong to the client " << it->second->get_nickname() << std::endl;
		std::vector<Channel*> cpy = it->second->get_channels_of_client();
		for (size_t l = 0; l <  cpy.size(); ++l)
    		std::cout << "Channel: " << cpy[l]->get_chan_name() << std::endl;
		std::cout << std::endl;	
	}
	
	std::cout << std::endl; 
	std::cout << "Next join test:\n" << std::endl;